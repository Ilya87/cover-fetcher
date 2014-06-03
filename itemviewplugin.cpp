#include "itemviewplugin.h"
#include "coverfetcher.h"
#include "settings.h"

#include <QtDebug>

ItemViewPlugin::ItemViewPlugin()
	: QObject()
{}

ItemViewPlugin::~ItemViewPlugin()
{
	_coverFetchers.clear();
}

QWidget * ItemViewPlugin::configPage()
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

QStringList ItemViewPlugin::classesToExtend()
{
	QStringList l = QStringList() << "LibraryTreeView" << "TagEditor";
	foreach (QString clazz, l) {
		CoverFetcher *cf = new CoverFetcher(this);
		_coverFetchers.insert(clazz, cf);
	}
	return l;
}

QAction * ItemViewPlugin::action(const QString &view, QMenu *parent)
{
	CoverFetcher *cf = _coverFetchers.value(view);
	QAction *a = cf->action(parent);
	return a;
}

void ItemViewPlugin::setSelectionModel(const QString &view, QItemSelectionModel *selectionModel)
{
	_coverFetchers.value(view)->setSelectionModel(selectionModel);
}
