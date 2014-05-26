#ifndef COVERFETCHER_H
#define COVERFETCHER_H

#include "fetchdialog.h"
#include <QItemSelectionModel>
#include <QMenu>
#include <QNetworkAccessManager>

#include "miamcore_global.h"

class MIAMCORE_LIBRARY CoverFetcher : public QObject
{
	Q_OBJECT
private:
	QItemSelectionModel *_selectionModel;
	FetchDialog *_fetchDialog;
	QNetworkAccessManager *_manager;

public:
	explicit CoverFetcher(QObject *parent);

	inline void setSelectionModel(QItemSelectionModel *selectionModel) { _selectionModel = selectionModel; }

	QAction * action(QMenu *parentMenu);

private slots:
	void fetch();
};

#endif // COVERFETCHER_H
