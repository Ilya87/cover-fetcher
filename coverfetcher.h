#ifndef COVERFETCHER_H
#define COVERFETCHER_H

#include "fetchdialog.h"
#include <QItemSelectionModel>
#include <QMenu>
#include <QNetworkAccessManager>
#include <QUrl>

#include "miamcore_global.h"

class MIAMCORE_LIBRARY CoverFetcher : public QObject
{
	Q_OBJECT
private:
	QItemSelectionModel *_selectionModel;
	FetchDialog *_fetchDialog;
	QNetworkAccessManager *_manager;
	QMap<QUrl, QString> _releasesGroup;

	Q_ENUMS(Fetch_Operations)

public:
	enum Fetch_Operations { Fetch_Artists = 0,
							Fetch_Releases = 1,
							Download_Cover = 2};
private:
	Fetch_Operations _currentCall;

public:
	explicit CoverFetcher(QObject *parent);

	inline void setSelectionModel(QItemSelectionModel *selectionModel) { _selectionModel = selectionModel; }

	QAction * action(QMenu *parentMenu);

private:
	static size_t uiLevenshteinDistance(const std::string &s1, const std::string &s2);

private slots:
	void fetch();

	void fetchArtists(const QByteArray &ba);

	void fetchReleases(const QByteArray &ba);
};

#endif // COVERFETCHER_H
