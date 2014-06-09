#ifndef COVERFETCHER_H
#define COVERFETCHER_H

#include "fetchdialog.h"
#include "model/selectedtracksmodel.h"
#include <QMenu>
#include <QNetworkAccessManager>
#include <QUrl>

#include "miamcore_global.h"

/**
 * \brief       The CoverFetcher class
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

	Q_ENUMS(Fetch_Operations)

public:
	enum Fetch_Operations { Fetch_Releases = 0,
							Download_Cover = 1};
private:
	//Fetch_Operations _currentCall;
	QMap<QUrl, Fetch_Operations> _currentCalls;

public:
	explicit CoverFetcher(QObject *parent);

	void setSelectedTracksModel(SelectedTracksModel *selectedTracksModel);

	QAction * action(QMenu *parentMenu);

private:
	static size_t uiLevenshteinDistance(const std::string &s1, const std::string &s2);

private slots:
	void dispatchReply(QNetworkReply *reply);

	void fetch();

	void fetchReleases(const QByteArray &ba);

//signals:
//	void refreshView();
};

#endif // COVERFETCHER_H
