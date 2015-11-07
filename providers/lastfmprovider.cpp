#include "lastfmprovider.h"

LastFMProvider::LastFMProvider(QObject *parent)
	: CoverArtProvider(parent)
{

}

QUrl LastFMProvider::query(const QString &expr)
{
	return QUrl("http://ws.audioscrobbler.com/2.0/?album.search=" + expr);
}

QUrl LastFMProvider::album(const QString &expr)
{
	return QUrl("http://ws.audioscrobbler.com/2.0/?album.getInfo=" + expr);
}
