#include "coverfetcher.h"
#include "sqldatabase.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStandardItemModel>
#include <QTemporaryFile>
#include <QUrl>
#include <QXmlStreamReader>

#include <QtDebug>

#include "ui_templateCover.h"

CoverFetcher::CoverFetcher(QObject *parent) :
	QObject(parent), _selectionModel(NULL)
{
	_fetchDialog = new FetchDialog;

	_manager = new QNetworkAccessManager(this);
	connect(_manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
		QXmlStreamReader xml(reply->readAll());

		QMap<QString, int> map;
		while(!xml.atEnd() && !xml.hasError()) {

			QXmlStreamReader::TokenType token = xml.readNext();
			if (token == QXmlStreamReader::StartDocument) {
				continue;
			}

			// Parse start elements
			if (token == QXmlStreamReader::StartElement) {
				if (xml.name() == "metadata") {
					continue;
				}
				if (xml.name() == "artist") {
					if (xml.attributes().hasAttribute("id")) {
						QStringRef sr = xml.attributes().value("id");
						qDebug() << sr;
						if (map.contains(sr.toString())) {
							int i = map.value(sr.toString());
							map.insert(sr.toString(), ++i);
						} else {
							map.insert(sr.toString(), 1);
						}
					}
				}
			}
		}
		int max = -1;
		QString mbid;
		QMapIterator<QString, int> it(map);
		while (it.hasNext()) {
			it.next();
			if (max < it.value()) {
				max = it.value();
				mbid = it.key();
			}
		}
		qDebug() << "highest mbid" << mbid;
		// reparse again the xml and ignore other mbid
		// find <release-group id="album-mbid"> matching the album
		// call cover art api with: album-mbid -> http://coverartarchive.org/release-group/{album-mbid}/front-{250|500}.jpg
		// behold: redirections
		// get the picture
		// display in the list (1, 2, ?)
		// attach to tag ?
		// copy to folder ?
	});
}

QAction * CoverFetcher::action(QMenu *parentMenu)
{
	QAction *action = new QAction("Fetch covers", parentMenu);
	connect(action, &QAction::triggered, this, &CoverFetcher::fetch);
	return action;
}

void CoverFetcher::fetch()
{
	QLayoutItem *child;
	while ((child = _fetchDialog->scrollAreaWidgetContents->layout()->takeAt(0)) != 0) {
		if (child->widget()) {
			delete child->widget();
		}
		delete child;
	}

	SqlDatabase db;
	db.open();
	QStringList artists;
	foreach (QModelIndex index, _selectionModel->selectedIndexes()) {
		if (index.column() == 0) {
			//qDebug() << _selectionModel->model() << index.column();
			QVariant v = index.data(Qt::UserRole + 1);
			if (v.isValid()) {
				/// FIXME: Magic numbers from LibraryTreeView class
				switch (v.toInt()) {
				case 0: {
					qDebug() << "fetch covers for this artist" << index.data();
					artists.append(index.data().toString());
					break;
				}
				case 1:
					qDebug() << "fetch cover for this album" << index.data();
					break;
				default:
					break;
				}
			}
		}
	}

	// TABLE tracks (artist varchar(255), artistAlbum varchar(255), album varchar(255),
	//				title varchar(255), trackNumber INTEGER, discNumber INTEGER, year INTEGER,
	//				absPath varchar(255) PRIMARY KEY ASC, path varchar(255),
	//				coverAbsPath varchar(255), internalCover INTEGER DEFAULT 0, externalCover INTEGER DEFAULT 0)
	foreach (QString artist, artists) {

		QLabel *labelArtist = new QLabel("Artist: " + artist);
		_fetchDialog->scrollAreaWidgetContents->layout()->addWidget(labelArtist);

		qDebug() << "fetching covers for" << artist;
		QNetworkRequest request(QUrl("http://musicbrainz.org/ws/2/release-group/?query=artist:%22" + artist + "%22"));
		request.setHeader(QNetworkRequest::UserAgentHeader, "MiamPlayer/0.6.3 ( https://github.com/MBach/Miam-Player )" );
		_manager->get(request);

		QSqlQuery q(db);
		q.prepare("SELECT DISTINCT album, coverAbsPath FROM tracks WHERE artist = ?");
		q.addBindValue(artist);

		if (q.exec()) {
			while (q.next()) {
				qDebug() << "q" << q.record().value(0);
				Ui_TemplateCovers templateCover;
				QWidget *covers = new QWidget;
				templateCover.setupUi(covers);
				// Fill the groupBox title with an Album from this Artist
				QString album = q.record().value(0).toString();
				templateCover.existingCoverGroupBox->setTitle(album);

				QSize s(_fetchDialog->coverValueSize(), _fetchDialog->coverValueSize());
				QSize s2(_fetchDialog->coverValueSize() + 10, _fetchDialog->coverValueSize() + 10);

				templateCover.currentCover->setDragDropMode(QListWidget::NoDragDrop);
				templateCover.currentCover->setIconSize(s);
				templateCover.currentCover->setMinimumSize(s2);
				templateCover.currentCover->setMaximumSize(s2);
				templateCover.remoteCovers->setDragDropMode(QListWidget::NoDragDrop);
				templateCover.remoteCovers->setIconSize(s);
				templateCover.remoteCovers->setMaximumHeight(s2.height());

				QListWidgetItem *currentCover = new QListWidgetItem();

				/// XXX: behold, internal covers are ignored
				if (!q.record().value(1).toString().isEmpty()) {
					currentCover->setIcon(QIcon(q.record().value(1).toString()));
				} else {
					currentCover->setIcon(QIcon(":/icons/disc"));
				}

				templateCover.currentCover->addItem(currentCover);
				_fetchDialog->scrollAreaWidgetContents->layout()->addWidget(covers);
			}
		}
	}

	QSpacerItem *vSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
	_fetchDialog->scrollAreaWidgetContents->layout()->addItem(vSpacer);
	db.close();

	_fetchDialog->show();
	_fetchDialog->activateWindow();
}
