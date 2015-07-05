#include "coverfetcher.h"
#include "model/sqldatabase.h"

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

#include "ui_templateCover.h"
#include "coverwidgetitemdelegate.h"
#include "filehelper.h"
#include "cover.h"
#include "settings.h"

#include <string>
#include <iostream>

#include <QtDebug>

using namespace std;

CoverFetcher::CoverFetcher(QObject *parent) :
	QObject(parent), _selectedTracksModel(nullptr)
{
	_fetchDialog = new FetchDialog;
	_manager = new QNetworkAccessManager(this);
	connect(_manager, &QNetworkAccessManager::finished, this, &CoverFetcher::dispatchReply);
}

void CoverFetcher::setSelectedTracksModel(SelectedTracksModel *selectedTracksModel)
{
	_selectedTracksModel = selectedTracksModel;
	/// XXX: wow, kind of hack no?
	connect(_fetchDialog, &FetchDialog::refreshView, this, [=]() {
		_selectedTracksModel->updateSelectedTracks();
	});
}

QAction * CoverFetcher::action(QMenu *parentMenu)
{
	QAction *action = new QAction(tr("Fetch covers"), parentMenu);
	connect(action, &QAction::triggered, this, &CoverFetcher::fetch);
	return action;
}

void CoverFetcher::dispatchReply(QNetworkReply *reply)
{
	//qDebug() << reply->isFinished() << reply->url();
	QByteArray ba = reply->readAll();
	QString path = QStandardPaths::writableLocation(QStandardPaths::TempLocation);

	// Dispatch request
	Fetch_Operations op = _currentCalls.value(reply->url());
	switch (op) {
	case Fetch_Releases:
		this->fetchReleases(ba);
		break;
	case Download_Cover: {
		// In case we don't get the picture at the first attempt, try again
		QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
		if (redirectionTarget.isNull()) {

			// The current covert has been downloaded to a temporary location, the lists can be populated
			QString tmpCoverPath = QDir::toNativeSeparators(path + "/" + reply->url().fileName());
			QPixmap pixmap;
			for (QGroupBox *gb : _fetchDialog->findChildren<QGroupBox*>()) {

				// It's possible to have a valid release but without cover yet :(
				if (gb->title() == _releasesGroup.value(reply->url()) && pixmap.loadFromData(ba)) {
					QListWidget *list = gb->findChild<QListWidget*>("remoteCovers");
					// list->clear();
					QListWidgetItem *item = new QListWidgetItem(list);
					item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
					item->setCheckState(Qt::Unchecked);
					item->setIcon(QIcon(pixmap));
					if (pixmap.save(tmpCoverPath)) {
						// Kind of ugly way to pass data from one class to another, but it does the job (at least an enum was created)
						item->setData(FetchDialog::LW_TmpCoverPath, tmpCoverPath);
					}
					break;
				}
			}
		} else {
			QUrl newUrl = reply->url().resolved(redirectionTarget.toUrl());
			QString release = _releasesGroup.value(reply->url());
			_releasesGroup.remove(reply->url());
			_releasesGroup.insert(newUrl, release);
			QNetworkReply *r = _manager->get(QNetworkRequest(newUrl));
			_currentCalls.insert(r->url(), Download_Cover);
		}
		break;
	}
	}
}

void CoverFetcher::fetch()
{
	_releasesGroup.clear();
	_currentCalls.clear();

	QStringList tracks = _selectedTracksModel->selectedTracks();
	SqlDatabase *db = SqlDatabase::instance();
	//db->open();

	// Format and concatenate all tracks in one big string. Replaces single quote with double quote
	QString l;
	l = tracks.join("\",\"").prepend("\"").append("\"");

	QString strArtistsAlbums = "SELECT DISTINCT art.name, alb.name, cover, internalCover, t.artistId, t.albumId " \
		"FROM tracks t INNER JOIN albums alb ON t.albumId = alb.id " \
		"INNER JOIN artists art ON alb.artistId = art.id WHERE t.uri IN (" + l + ") " \
		"ORDER BY art.name, alb.year";
	QString artistId, albumId;

	qDebug() << "query" << strArtistsAlbums;

	QSqlQuery qArtistsAlbums(*db);
	qArtistsAlbums.exec(strArtistsAlbums);

	QString prevArtist = "";
	int size = Settings::instance()->value("CoverFetcher/coverValueSize").toInt();
	QSize s(size, size);
	QSize s2(size + 10, size + 10);
	while (qArtistsAlbums.next()) {
		QString artist = qArtistsAlbums.record().value(0).toString();
		QString album = qArtistsAlbums.record().value(1).toString();
		qDebug() << Q_FUNC_INFO << "searching for covers:" << artist << album;
		QString cover = qArtistsAlbums.record().value(2).toString();
		bool internalCover = qArtistsAlbums.record().value(3).toBool();
		artistId = qArtistsAlbums.record().value(4).toString();
		albumId = qArtistsAlbums.record().value(5).toString();

		// Send a new request for fetching artists only if it's a new one
		if (artist != prevArtist) {
			QLabel *labelArtist = new QLabel("Artist: " + artist);
			_fetchDialog->scrollAreaWidgetContents->layout()->addWidget(labelArtist);

			QString tmp = QUrl::toPercentEncoding(artist);
			QNetworkRequest request(QUrl("http://musicbrainz.org/ws/2/release-group/?query=artist:%22" + tmp + "%22;limit=100"));
			request.setHeader(QNetworkRequest::UserAgentHeader, "MiamPlayer/0.7.0 ( https://github.com/MBach/Miam-Player )" );
			QNetworkReply *n = _manager->get(request);
			_currentCalls.insert(n->url(), Fetch_Releases);
		}

		Ui_TemplateCovers templateCover;
		QWidget *covers = new QWidget(_fetchDialog);
		templateCover.setupUi(covers);
		// Fill the groupBox title with an Album from this Artist
		templateCover.albumCoverGroupBox->setTitle(album);

		/// TODO: animate gif
		/*QListWidgetItem *remoteTmpCover = new QListWidgetItem;
		remoteTmpCover->setIcon(QIcon(":/loading"));
		remoteTmpCover->setText();
		templateCover.remoteCovers->addItem(remoteTmpCover);*/

		QListWidgetItem *currentCover = new QListWidgetItem;
		currentCover->setData(FetchDialog::LW_Artist, artistId);
		currentCover->setData(FetchDialog::LW_Album, albumId);

		if (cover.isEmpty() && internalCover == false) {
			currentCover->setIcon(QIcon(":/icons/disc"));
		} else if (internalCover) {
			QSqlQuery oneTrack(*db);
			oneTrack.prepare("SELECT uri FROM tracks WHERE artistId = ? AND albumId = ? LIMIT 1");
			oneTrack.addBindValue(artistId);
			oneTrack.addBindValue(albumId);
			if (oneTrack.exec() && oneTrack.next()) {
				FileHelper fh(oneTrack.record().value(0).toString());
				QPixmap p;
				Cover *c = fh.extractCover();
				if (c && p.loadFromData(c->byteArray())) {
					currentCover->setIcon(p);
				}
				delete c;
			}
		} else {
			currentCover->setIcon(QIcon(cover));
		}
		templateCover.currentCover->addItem(currentCover);
		_fetchDialog->scrollAreaWidgetContents->layout()->addWidget(covers);
		prevArtist = artist;
	}

	// Initialize size with right value from slider
	for (QListWidget *list : _fetchDialog->findChildren<QListWidget*>()) {
		list->setDragDropMode(QListWidget::NoDragDrop);
		list->setIconSize(s);
		list->setMinimumSize(s2);
		list->setMaximumSize(s2);
		list->setItemDelegate(new CoverWidgetItemDelegate(list));
	}

	QSpacerItem *vSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
	_fetchDialog->scrollAreaWidgetContents->layout()->addItem(vSpacer);
	//db->close();

	_fetchDialog->show();
	_fetchDialog->activateWindow();
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
		//qDebug() << "while:" << it.key() << it.value();
		for (QGroupBox *gb : _fetchDialog->findChildren<QGroupBox*>()) {
			if (uiLevenshteinDistance(gb->title().toLower().toStdString(), it.key().toStdString()) < 4 ||
					it.key().contains(gb->title().toLower()) || gb->title().toLower().contains(it.key())) {
				//qDebug() << "uiLevenshteinDistance: get the covert art for " << gb->title() << it.key() << it.value();
				/// FIXME: find a way to get the 500px thumbnail and to automatically download the large one after
				QUrl url("http://coverartarchive.org/release-group/" + it.value() + "/front");
				QNetworkRequest request(url);
				request.setHeader(QNetworkRequest::UserAgentHeader, "MiamPlayer/0.7.0 ( https://github.com/MBach/Miam-Player )" );
				_releasesGroup.insert(url, gb->title());
				QNetworkReply *reply = _manager->get(request);
				_currentCalls.insert(reply->url(), Download_Cover);
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
