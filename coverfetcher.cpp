#include "coverfetcher.h"
#include "sqldatabase.h"

#include <QDir>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStandardItemModel>
#include <QStandardPaths>
#include <QUrl>
#include <QXmlStreamReader>

#include <QtDebug>

#include "ui_templateCover.h"
#include "coverwidgetitemdelegate.h"

#include <string>
#include <iostream>

using namespace std;

CoverFetcher::CoverFetcher(QObject *parent) :
	QObject(parent), _selectionModel(NULL)
{
	_fetchDialog = new FetchDialog;

	_manager = new QNetworkAccessManager(this);
	connect(_manager, &QNetworkAccessManager::finished, this, &CoverFetcher::dispatchReply);
}

QAction * CoverFetcher::action(QMenu *parentMenu)
{
	QAction *action = new QAction("Fetch covers", parentMenu);
	connect(action, &QAction::triggered, this, &CoverFetcher::fetch);
	return action;
}

void CoverFetcher::dispatchReply(QNetworkReply *reply)
{
	QByteArray ba = reply->readAll();
	// Dispatch request
	switch (_currentCall) {
	case Fetch_Artists:
		this->fetchArtists(ba);
		break;
	case Fetch_Releases:
		break;
	case Download_Cover: {
		// In case we don't get the picture at the first attempt
		QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
		if (redirectionTarget.isNull()) {
			// The current covert has been downloaded, now we can populate the lists
			QPixmap pixmap;
			foreach (QGroupBox *gb, _fetchDialog->findChildren<QGroupBox*>()) {
				// It's possible to have a valid release but without cover yet :(
				if (gb->title() == _releasesGroup.value(reply->url()) && pixmap.loadFromData(ba)) {
					QListWidget *list = gb->findChild<QListWidget*>("remoteCovers");
					QListWidgetItem *item = new QListWidgetItem(list);
					item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
					item->setCheckState(Qt::Unchecked);
					item->setIcon(QIcon(pixmap));
					break;
				}
			}
		} else {
			QUrl newUrl = reply->url().resolved(redirectionTarget.toUrl());
			QString release = _releasesGroup.value(reply->url());
			_releasesGroup.remove(reply->url());
			_releasesGroup.insert(newUrl, release);
			_manager->get(QNetworkRequest(newUrl));
		}
		break;
	}
	}
}

void CoverFetcher::fetch()
{
	_releasesGroup.clear();

	QStringList artists;
	foreach (QModelIndex index, _selectionModel->selectedIndexes()) {
		if (index.column() == 0) {
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
	SqlDatabase db;
	db.open();
	foreach (QString artist, artists) {

		QLabel *labelArtist = new QLabel("Artist: " + artist);
		_fetchDialog->scrollAreaWidgetContents->layout()->addWidget(labelArtist);

		qDebug() << "fetching covers for" << artist;
		QNetworkRequest request(QUrl("http://musicbrainz.org/ws/2/release-group/?query=artist:%22" + artist + "%22;limit=100"));
		request.setHeader(QNetworkRequest::UserAgentHeader, "MiamPlayer/0.6.3 ( https://github.com/MBach/Miam-Player )" );
		_currentCall = Fetch_Artists;
		_manager->get(request);

		QSqlQuery q(db);
		q.prepare("SELECT DISTINCT album, coverAbsPath FROM tracks WHERE artist = ?");
		q.addBindValue(artist);

		if (q.exec()) {
			while (q.next()) {
				qDebug() << "q" << q.record().value(0);
				Ui_TemplateCovers templateCover;
				QWidget *covers = new QWidget(_fetchDialog);
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
				templateCover.currentCover->setItemDelegate(new CoverWidgetItemDelegate(templateCover.currentCover));

				templateCover.remoteCovers->setDragDropMode(QListWidget::NoDragDrop);
				templateCover.remoteCovers->setIconSize(s);
				templateCover.remoteCovers->setMaximumHeight(s2.height());
				templateCover.remoteCovers->setItemDelegate(new CoverWidgetItemDelegate(templateCover.remoteCovers));

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

void CoverFetcher::fetchArtists(const QByteArray &ba)
{
	/*QXmlStreamReader xml(ba);
	QMap<QString, int> map;
	while(!xml.atEnd() && !xml.hasError()) {

		QXmlStreamReader::TokenType token = xml.readNext();
		// Parse start elements
		if (token == QXmlStreamReader::StartElement) {
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
	qDebug() << "highest mbid" << mbid;
	while (it.hasNext()) {
		it.next();
		if (max < it.value()) {
			max = it.value();
			mbid = it.key();
		}
	}*/
	this->fetchReleases(ba);
}

void CoverFetcher::fetchReleases(const QByteArray &ba)
{
	QXmlStreamReader xml(ba);

	// Album Text -> Album ID
	QMap<QString, QString> map;
	while(!xml.atEnd() && !xml.hasError()) {

		QXmlStreamReader::TokenType token = xml.readNext();

		// Parse start elements
		if (token == QXmlStreamReader::StartElement) {
			if (xml.name() == "release-group") {
				if (xml.attributes().hasAttribute("id")) {
					QStringRef sr = xml.attributes().value("id");
					if (xml.readNextStartElement() && xml.name() == "title") {
						map.insert(xml.readElementText().toLower(), sr.toString());
					}
				}
			}
		}
	}

	QMapIterator<QString, QString> it(map);
	/// Complexity: should be improved!
	while (it.hasNext()) {
		it.next();
		qDebug() << "while:" << it.key() << it.value();
		foreach (QGroupBox *gb, _fetchDialog->findChildren<QGroupBox*>()) {
			qDebug() << "foreach:" << gb->title();
			if (it.key().contains(gb->title().toLower()) || gb->title().toLower().contains(it.key()) ||
					uiLevenshteinDistance(gb->title().toLower().toStdString(), it.key().toStdString()) < 2) {
				qDebug() << "uiLevenshteinDistance: get the covert art for " << gb->title() << it.key() << it.value();
				/// FIXME: find a way to get the 500px thumbnail and to automatically download the large one after
				QUrl url("http://coverartarchive.org/release-group/" + it.value() + "/front");
				QNetworkRequest request(url);
				request.setHeader(QNetworkRequest::UserAgentHeader, "MiamPlayer/0.6.3 ( https://github.com/MBach/Miam-Player )" );
				_currentCall = Download_Cover;
				_releasesGroup.insert(url, gb->title());
				_manager->get(request);
				//it.remove();
				break;
			}
		}
	}
}

// Compute Levenshtein Distance
// Martin Ettl, 2012-10-05

size_t CoverFetcher::uiLevenshteinDistance(const std::string &s1, const std::string &s2)
{
	const size_t m(s1.size());
	const size_t n(s2.size());

	if (m==0) return n;
	if (n==0) return m;

	size_t *costs = new size_t[n + 1];

	for (size_t k = 0; k <= n; k++) costs[k] = k;

	size_t i = 0;
	for (string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i) {
		costs[0] = i+1;
		size_t corner = i;

		size_t j = 0;
		for (string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j) {
			size_t upper = costs[j+1];
			if (*it1 == *it2) {
				costs[j+1] = corner;
			} else {
				size_t t(upper < corner ? upper : corner);
				costs[j+1] = (costs[j] < t ? costs[j] : t) + 1;
			}
			corner = upper;
		}
	}

	size_t result = costs[n];
	delete [] costs;

	return result;
}
