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
	QMap<QUrl, QString> _releasesGroup;
	QList<CoverArtProvider*> _providers;

	Q_ENUMS(Fetch_Operations)

public:
	enum Fetch_Operations : int
	{
		FO_GetReleases		= 0,
		FO_DownloadCover	= 1,
		FO_Search			= 2
	};

private:
	QMap<QUrl, Fetch_Operations> _currentCalls;

	QSet<QNetworkReply*> _currentCalls2;

public:
	explicit CoverFetcher(QObject *parent);

	void setSelectedTracksModel(SelectedTracksModel *selectedTracksModel);

	QAction * action(QMenu *parentMenu);

private:
	/** Levenshtein distance is a string metric for measuring the difference between two sequences. */
	static size_t uiLevenshteinDistance(const std::string &s1, const std::string &s2);

	void downloadCover(QByteArray ba, QNetworkReply *reply);

private slots:
	void dispatchReply(QNetworkReply *reply);

	void fetch();
};

#endif // COVERFETCHER_H
