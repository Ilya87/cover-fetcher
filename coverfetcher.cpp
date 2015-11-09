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

#include "ui_templateCover.h"
#include "coverwidgetitemdelegate.h"
#include "filehelper.h"
#include "cover.h"
#include "settings.h"
#include "providers/amazonprovider.h"
#include "providers/lastfmprovider.h"
#include "providers/musicbrainzprovider.h"

#include <string>
#include <iostream>

#include <QtDebug>

CoverFetcher::CoverFetcher(QObject *parent)
	: QObject(parent)
	, _selectedTracksModel(nullptr)
	, _fetchDialog(nullptr)
	, _manager(new QNetworkAccessManager(this))
{
	_providers.append(new MusicBrainzProvider(_manager));
	_providers.append(new AmazonProvider(_manager));
	//_providers.append(new LastFMProvider(_manager));
}

/** Entry point. */
void CoverFetcher::fetch(SelectedTracksModel *selectedTracksModel)
{
	qDebug() << Q_FUNC_INFO;
	if (_fetchDialog == nullptr) {
		_fetchDialog = new FetchDialog;
	}

	_selectedTracksModel = selectedTracksModel;
	/// XXX: wow, kind of hack no?
	connect(_fetchDialog, &FetchDialog::refreshView, this, [=]() {
		_selectedTracksModel->updateSelectedTracks();
	});

	QStringList tracks = _selectedTracksModel->selectedTracks();
	SqlDatabase *db = SqlDatabase::instance();

	// Format and concatenate all tracks in one big string. Replaces single quote with double quote
	/// FIXME
	QString l;
	l = tracks.join("\",\"").prepend("\"").append("\"");

	QString strArtistsAlbums = "SELECT DISTINCT art.name, alb.name, cover, internalCover, t.artistId, t.albumId " \
		"FROM tracks t INNER JOIN albums alb ON t.albumId = alb.id " \
		"INNER JOIN artists art ON alb.artistId = art.id WHERE t.uri IN (" + l + ") " \
		"ORDER BY art.name, alb.year";
	QString artistId, albumId;

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
		}

		// Query all registered providers
		for (CoverArtProvider *cp : _providers) {
			QUrl url = cp->query(artist, album);
			QNetworkRequest request(url);
			request.setAttribute(QNetworkRequest::User, CoverArtProvider::FO_Search);
			request.setHeader(QNetworkRequest::UserAgentHeader, "MiamPlayer/0.8.0 ( http://www.miam-player.org/ )" );
			QNetworkReply *n = _manager->get(request);
			n->setProperty("requestType", CoverArtProvider::FO_Search);
			connect(n, &QNetworkReply::finished, this, [=]() {
				cp->dispatchReply(n);
			});
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
	_fetchDialog->show();
	_fetchDialog->activateWindow();
}
