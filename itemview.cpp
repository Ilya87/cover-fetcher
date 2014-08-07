#include "itemview.h"
#include "coverfetcher.h"
#include "settings.h"

#include <QtDebug>

ItemView::ItemView()
	: QObject()
{
	Settings *settings = Settings::getInstance();
	if (!settings->value("CoverFetcher/coverValueSize").isValid()) {
		settings->setValue("CoverFetcher/coverValueSize", 64);
		settings->setValue("CoverFetcher/integrateCoverToFiles", true);
	}
}

ItemView::~ItemView()
{
	_coverFetchers.clear();
}

QWidget * ItemView::configPage()
{
	QWidget *widget = new QWidget();
	_ui.setupUi(widget);
	Settings *settings = Settings::getInstance();
	settings->beginGroup("CoverFetcher");
	_ui.radioButtonIntegrateCover->setChecked(settings->value("integrateCoverToFiles", true).toBool());
	settings->endGroup();

	connect(_ui.radioButtonIntegrateCover, &QRadioButton::toggled, this, [=](bool b) {
		settings->beginGroup("CoverFetcher");
		settings->setValue("integrateCoverToFiles", b);
		settings->endGroup();
	});
	return widget;
}

QStringList ItemView::classesToExtend()
{
	QStringList l = QStringList() << "LibraryTreeView" << "TagEditor";
	foreach (QString clazz, l) {
		CoverFetcher *cf = new CoverFetcher(this);
		_coverFetchers.insert(clazz, cf);
	}
	return l;
}

QAction * ItemView::action(const QString &view, QMenu *parent)
{
	CoverFetcher *cf = _coverFetchers.value(view);
	QAction *a = cf->action(parent);
	return a;
}

void ItemView::setSelectedTracksModel(const QString &view, SelectedTracksModel *selectedTracksModel)
{
	_coverFetchers.value(view)->setSelectedTracksModel(selectedTracksModel);
}
