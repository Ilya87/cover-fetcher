#ifndef LASTFMPROVIDER_H
#define LASTFMPROVIDER_H

#include "coverartprovider.h"

class MIAMCORE_LIBRARY LastFMProvider : public CoverArtProvider
{
public:
	explicit LastFMProvider(QNetworkAccessManager *parent);

	virtual QUrl query(const QString &artist, const QString &album) override;

	virtual QUrl album(const QString &expr) override;
};

#endif // LASTFMPROVIDER_H
