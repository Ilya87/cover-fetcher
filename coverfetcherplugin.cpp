#include "coverfetcherplugin.h"
#include "coverfetcher.h"
#include "settings.h"

#include <QtDebug>

CoverFetcherPlugin::CoverFetcherPlugin(QObject *parent)
	: ItemViewPlugin(parent)
	, _coverFetcher(new CoverFetcher(this))
{
	Settings *settings = Settings::instance();
	if (!settings->value("CoverFetcher/coverValueSize").isValid()) {
		settings->setValue("CoverFetcher/coverValueSize", 64);
		settings->setValue("CoverFetcher/integrateCoverToFiles", true);
	}
}

CoverFetcherPlugin::~CoverFetcherPlugin()
{
	//qDeleteAll(_coverFetchers.values());
}

QWidget * CoverFetcherPlugin::configPage()
{
	qDebug() << Q_FUNC_INFO;
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
	return l;
}

QAction * CoverFetcherPlugin::action(const QString &view, QMenu *parentMenu)
{
	QAction *action = new QAction(tr("Fetch covers"), parentMenu);
	qDebug() << Q_FUNC_INFO << view << parentMenu;
	connect(action, &QAction::triggered, this, [=]() {
		SelectedTracksModel *s = _viewModels.value(view);
		_coverFetcher->fetch(s);
	});
	return action;
}

void CoverFetcherPlugin::setSelectedTracksModel(const QString &view, SelectedTracksModel *selectedTracksModel)
{
	qDebug() << Q_FUNC_INFO << view << selectedTracksModel;
	_viewModels.insert(view, selectedTracksModel);
}
