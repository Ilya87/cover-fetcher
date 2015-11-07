#ifndef LASTFMPROVIDER_H
#define LASTFMPROVIDER_H

#include "coverartprovider.h"

class MIAMCORE_LIBRARY LastFMProvider : public CoverArtProvider
{
public:
	explicit LastFMProvider(QObject *parent = nullptr);

	virtual QUrl query(const QString &expr) override;

	virtual QUrl album(const QString &expr) override;
};

#endif // LASTFMPROVIDER_H
