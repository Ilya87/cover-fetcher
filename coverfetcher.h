#ifndef COVERFETCHER_H
#define COVERFETCHER_H

#include <QItemSelectionModel>
#include <QMenu>

#include "miamcore_global.h"

class MIAMCORE_LIBRARY CoverFetcher : public QObject
{
	Q_OBJECT
private:
	QItemSelectionModel *_selectionModel;

public:
	explicit CoverFetcher(QObject *parent);

	inline void setSelectionModel(QItemSelectionModel *selectionModel) { _selectionModel = selectionModel; }

	QAction * action(QMenu *parentMenu);

private slots:
	void fetch();
};

#endif // COVERFETCHER_H
