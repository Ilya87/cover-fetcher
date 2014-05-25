#include "itemviewplugin.h"
#include "coverfetcher.h"

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
	/// TODO
	return new QWidget();
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
	//QAction *fetch = new QAction(tr("Fetch covers"), parent);
	CoverFetcher *cf = _coverFetchers.value(view);
	QAction *a = cf->action(parent);
	return a;
}

void ItemViewPlugin::setSelectionModel(const QString &view, QItemSelectionModel *selectionModel)
{
	_coverFetchers.value(view)->setSelectionModel(selectionModel);
}
