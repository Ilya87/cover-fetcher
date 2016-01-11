#include "coverfetcherplugin.h"
#include "settings.h"
#include "model/sqldatabase.h"
#include "ui_templateCover.h"
#include "filehelper.h"
#include "cover.h"
#include "coverwidgetitemdelegate.h"
#include "providers/amazonprovider.h"
#include "providers/musicbrainzprovider.h"

#include <QSqlQuery>
#include <QSqlRecord>

#include <QtDebug>

CoverFetcherPlugin::CoverFetcherPlugin(QObject *parent)
	: ItemViewPlugin(parent)
	, _fetchDialog(nullptr)
	, _manager(new QNetworkAccessManager(this))
{
	Settings *settings = Settings::instance();
	if (!settings->value("CoverFetcher/coverValueSize").isValid()) {
		settings->setValue("CoverFetcher/coverValueSize", 64);
		settings->setValue("CoverFetcher/integrateCoverToFiles", true);
	}
	if (!settings->value("CoverFetcher/musicbrainzCheckBox").isValid()) {
		settings->setValue("CoverFetcher/musicbrainzCheckBox", true);
	}
	if (!settings->value("CoverFetcher/amazonCheckBox").isValid()) {
		settings->setValue("CoverFetcher/amazonCheckBox", true);
	}
	if (settings->value("CoverFetcher/musicbrainzCheckBox").toBool()) {
		_providers.append(new MusicBrainzProvider(_manager));
	}
	if (settings->value("CoverFetcher/amazonCheckBox").toBool()) {
		_providers.append(new AmazonProvider(_manager));
	}
	for (CoverArtProvider *cap : _providers) {
		connect(cap, &CoverArtProvider::aboutToCreateCover, this, &CoverFetcherPlugin::addCover);
	}

	// Dispatch replies to specialized class
	connect(_manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
		for (CoverArtProvider *cp : _providers) {
			if (cp->type() == reply->property("type").toInt()) {
				cp->dispatchReply(reply);
			}
		}
	});
}

CoverFetcherPlugin::~CoverFetcherPlugin()
{
	qDeleteAll(_providers);
}

/** Generate UI in lazy loading mode. */
QWidget * CoverFetcherPlugin::configPage()
{
	QWidget *widget = new QWidget;
	_ui.setupUi(widget);
	Settings *settings = Settings::instance();
	_ui.radioButtonIntegrateCover->setChecked(settings->value("CoverFetcher/integrateCoverToFiles", true).toBool());

	// Init items at startup
	QList<QCheckBox*> providerList;
	providerList << _ui.musicbrainzCheckBox << _ui.amazonCheckBox << _ui.discogsCheckBox << _ui.lastfmCheckBox;
	for (QCheckBox *p : providerList) {
		p->setChecked(settings->value("CoverFetcher/" + p->objectName()).toBool());
		connect(p, &QCheckBox::toggled, this, [=](bool enabled) { this->manageProvider(enabled, p); });
	}

	connect(_ui.radioButtonIntegrateCover, &QRadioButton::toggled, this, [=](bool b) {
		settings->setValue("CoverFetcher/integrateCoverToFiles", b);
	});
	return widget;
}

QStringList CoverFetcherPlugin::classesToExtend()
{
	QStringList l = QStringList() << "LibraryTreeView" << "TagEditor";
	return l;
}

QAction * CoverFetcherPlugin::action(const QString &view, QMenu *parentMenu)
{
	QAction *action = new QAction(tr("Fetch covers"), parentMenu);
	connect(action, &QAction::triggered, this, [=]() { this->fetch(_viewModels.value(view)); });
	return action;
}

void CoverFetcherPlugin::setSelectedTracksModel(const QString &view, SelectedTracksModel *selectedTracksModel)
{
	_viewModels.insert(view, selectedTracksModel);
}

/** Entry point. */
void CoverFetcherPlugin::fetch(SelectedTracksModel *selectedTracksModel)
{
	qDebug() << Q_FUNC_INFO;
	if (_fetchDialog == nullptr) {
		_fetchDialog = new FetchDialog;
	}

	/// XXX: wow, kind of hack no?
	connect(_fetchDialog, &FetchDialog::refreshView, this, [=]() {
		selectedTracksModel->updateSelectedTracks();
	});

	QStringList tracks = selectedTracksModel->selectedTracks();
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
			n->setProperty("type", cp->type());
			n->setProperty("requestType", CoverArtProvider::FO_Search);
			n->setProperty("artist", artist);
			n->setProperty("album", album);
		}

		Ui_TemplateCovers templateCover;
		QWidget *covers = new QWidget(_fetchDialog);
		templateCover.setupUi(covers);
		// Fill the groupBox title with an Album from this Artist
		templateCover.albumCoverGroupBox->setTitle(album);
		templateCover.albumCoverGroupBox->layout()->setSizeConstraint(QLayout::SetMaximumSize);
		//templateCover.layout()->setSizeConstraint(QLayout::SetMaximumSize);

		templateCover.albumCoverGroupBox->setMinimumHeight(size + 10);
		templateCover.albumCoverGroupBox->setMinimumWidth(size + 10);
		templateCover.albumCoverGroupBox->setMaximumHeight(size + 10);
		templateCover.albumCoverGroupBox->setMaximumWidth(size + 10);

		//templateCover.remoteCoversGroupBox->setMinimumHeight(size + 10);
		//templateCover.remoteCoversGroupBox->setMinimumWidth(size + 10);
		//templateCover.remoteCoversGroupBox->setMaximumHeight(size + 10);
		//templateCover.remoteCoversGroupBox->setMaximumWidth(size + 10);

		//QLayoutItem *itemLayout = templateCover.remoteCoversGroupBox->layout()->itemAt(0);
		//qDebug() << Q_FUNC_INFO << itemLayout->widget();

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
		//list->setDragDropMode(QListWidget::NoDragDrop);
		list->setIconSize(s);
		//list->setMinimumSize(s2);
		//list->setMaximumSize(s2);
		list->setItemDelegate(new CoverWidgetItemDelegate(list));
	}

	QSpacerItem *vSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
	_fetchDialog->scrollAreaWidgetContents->layout()->addItem(vSpacer);
	_fetchDialog->show();
	_fetchDialog->activateWindow();
}

/** When one is checking items in the list, providers are added or removed dynamically. */
void CoverFetcherPlugin::manageProvider(bool enabled, QCheckBox *checkBox)
{
	Settings::instance()->setValue("CoverFetcher/" + checkBox->objectName(), enabled);
	if (enabled) {
		int type = checkBox->property("type").toInt();
		CoverArtProvider *cap = nullptr;
		switch(type) {
		case CoverArtProvider::PT_MusicBrainz:
			cap = new MusicBrainzProvider(_manager);
			break;
		case CoverArtProvider::PT_Amazon:
			cap = new AmazonProvider(_manager);
			break;
		/// TODO: other providers
		default:
			break;
		}
		if (cap != nullptr) {
			_providers.append(cap);
			connect(cap, &CoverArtProvider::aboutToCreateCover, this, &CoverFetcherPlugin::addCover);
		}
	} else {
		QListIterator<CoverArtProvider*> it(_providers);
		while (it.hasNext()) {
			auto cap = it.next();
			if (cap->type() == checkBox->property("type").toInt()) {
				_providers.removeAll(cap);
				delete cap;
				break;
			}
		}
	}
}

void CoverFetcherPlugin::addCover(const QString &album, const QPixmap &cover)
{
	qDebug() << Q_FUNC_INFO << album;
	for (QGroupBox *gb : _fetchDialog->findChildren<QGroupBox*>("albumCoverGroupBox")) {

		qDebug() << Q_FUNC_INFO << gb->layout()->sizeConstraint();
		if (gb->title() == album) {
			QListWidget *list = gb->findChild<QListWidget*>("remoteCovers");
			QListWidgetItem *item = new QListWidgetItem(list);
			item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
			item->setCheckState(Qt::Unchecked);
			item->setIcon(QIcon(cover));
			/*if (cover.save(tmpCoverPath)) {
				// Kind of ugly way to pass data from one class to another, but it does the job (at least an enum was created)
				item->setData(FetchDialog::LW_TmpCoverPath, tmpCoverPath);
			}*/
			break;
		}
	}
}
