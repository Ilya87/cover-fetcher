#include "coverfetcher.h"

#include <QtDebug>

CoverFetcher::CoverFetcher(QObject *parent) :
	QObject(parent), _selectionModel(NULL)
{
}

QAction * CoverFetcher::action(QMenu *parentMenu)
{
	QAction *action = new QAction("Fetch covers", parentMenu);
	connect(action, &QAction::triggered, this, &CoverFetcher::fetch);
	return action;
}

void CoverFetcher::fetch()
{
	qDebug() << "get the QModelIndex, query DB, and fetch online" << sender();
	QAction *action = qobject_cast<QAction*>(sender());
	qDebug() << _selectionModel->model() << _selectionModel->selectedIndexes();
}
