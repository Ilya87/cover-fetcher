#ifndef MUSICBRAINZPROVIDER_H
#define MUSICBRAINZPROVIDER_H

#include "coverartprovider.h"

/**
 * \brief		The MusicBrainzProvider class implements a way to query and return images from MusicBrainz (and coverartarchive) webservice.
 * \author      Matthieu Bachelier
 * \copyright   GNU General Public License v3
 */
class MIAMCORE_LIBRARY MusicBrainzProvider : public CoverArtProvider
{
	Q_OBJECT
private:
	QMap<QUrl, QString> _releasesGroup;

public:
	explicit MusicBrainzProvider(QNetworkAccessManager *manager);

	virtual QUrl query(const QString &artist, const QString &album) override;

	virtual QUrl album(const QString &albumId) override;

private:
	/** Levenshtein distance is a string metric for measuring the difference between two sequences. */
	static size_t uiLevenshteinDistance(const std::string &s1, const std::string &s2);

	void downloadCover(QByteArray ba, QNetworkReply *reply);

	void fetchReleases(const QByteArray &ba);

public slots:
	virtual void dispatchReply(QNetworkReply *reply) override;
};

#endif // MUSICBRAINZPROVIDER_H
