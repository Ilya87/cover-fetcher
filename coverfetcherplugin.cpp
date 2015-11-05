#include "coverfetcherplugin.h"
#include "coverfetcher.h"
#include "settings.h"

#include <QtDebug>

CoverFetcherPlugin::CoverFetcherPlugin(QObject *parent)
	: ItemViewPlugin(parent)
{
	Settings *settings = Settings::instance();
	if (!settings->value("CoverFetcher/coverValueSize").isValid()) {
		settings->setValue("CoverFetcher/coverValueSize", 64);
		settings->setValue("CoverFetcher/integrateCoverToFiles", true);
	}
}

CoverFetcherPlugin::~CoverFetcherPlugin()
{
	qDeleteAll(_coverFetchers.values());
}

QWidget * CoverFetcherPlugin::configPage()
{
	QWidget *widget = new QWidget;
	_ui.setupUi(widget);
	Settings *settings = Settings::instance();
	settings->beginGroup("CoverFetcher");
	_ui.radioButtonIntegrateCover->setChecked(settings->value("integrateCoverToFiles", true).toBool());

	// Init items at startup
	QStringList providers = QStringList() << "Discogs" << "Amazon" << "Last.FM";
	for (QString provider : providers) {
		bool isChecked = settings->value(provider).toBool();
		Qt::CheckState state = Qt::Checked;
		if (!isChecked) {
			state = Qt::Unchecked;
		}
		_ui.coverProviderListWidget->findItems(provider, Qt::MatchExactly).first()->setCheckState(state);
	}
	settings->endGroup();

	connect(_ui.radioButtonIntegrateCover, &QRadioButton::toggled, this, [=](bool b) {
		settings->beginGroup("CoverFetcher");
		settings->setValue("integrateCoverToFiles", b);
		settings->endGroup();
	});

	connect(_ui.coverProviderListWidget, &QListWidget::itemChanged, this, [=](QListWidgetItem *item) {
		settings->beginGroup("CoverFetcher");
		settings->setValue(item->text(), (item->checkState() == Qt::Checked));
		settings->endGroup();
	});
	return widget;
}

QStringList CoverFetcherPlugin::classesToExtend()
{
	QStringList l = QStringList() << "LibraryTreeView" << "TagEditor";
	for (QString clazz : l) {
		CoverFetcher *cf = new CoverFetcher(this);
		_coverFetchers.insert(clazz, cf);
	}
	return l;
}

QAction * CoverFetcherPlugin::action(const QString &view, QMenu *parent)
{
	CoverFetcher *cf = _coverFetchers.value(view);
	QAction *a = cf->action(parent);
	return a;
}

void CoverFetcherPlugin::setSelectedTracksModel(const QString &view, SelectedTracksModel *selectedTracksModel)
{
	_coverFetchers.value(view)->setSelectedTracksModel(selectedTracksModel);
}
