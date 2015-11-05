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
public:
	explicit MusicBrainzProvider(QObject *parent = nullptr);

	virtual ~MusicBrainzProvider();

	virtual QUrl query(const QString &expr) override;

	virtual QUrl album(const QString &expr) override;

};

#endif // MUSICBRAINZPROVIDER_H
