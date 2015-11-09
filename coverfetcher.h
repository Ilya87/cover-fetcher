#ifndef COVERFETCHER_H
#define COVERFETCHER_H

#include "model/selectedtracksmodel.h"
#include "providers/coverartprovider.h"
#include "fetchdialog.h"

#include <QMenu>
#include <QNetworkAccessManager>
#include <QUrl>

#include "miamcore_global.h"

/**
 * \brief       The CoverFetcher class can connect to the Web for downloading remote covers into your file-system.
 * \author      Matthieu Bachelier
 * \copyright   GNU General Public License v3
 */
class MIAMCORE_LIBRARY CoverFetcher : public QObject
{
	Q_OBJECT
private:
	SelectedTracksModel *_selectedTracksModel;
	FetchDialog *_fetchDialog;
	QNetworkAccessManager *_manager;
	QList<CoverArtProvider*> _providers;

public:
	explicit CoverFetcher(QObject *parent);

public slots:
	/** Entry point. */
	void fetch(SelectedTracksModel *selectedTracksModel);
};

#endif // COVERFETCHER_H
