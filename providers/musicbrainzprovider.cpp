#include "musicbrainzprovider.h"

#include <QtDebug>

MusicBrainzProvider::MusicBrainzProvider(QObject *parent)
	: CoverArtProvider(parent)
{

}

MusicBrainzProvider::~MusicBrainzProvider()
{

}

QUrl MusicBrainzProvider::query(const QString &expr)
{
	return QUrl("http://musicbrainz.org/ws/2/release-group/?query=artist:%22" + expr + "%22;limit=100");
}

QUrl MusicBrainzProvider::album(const QString &expr)
{
	return QUrl("http://coverartarchive.org/release-group/" + expr + "/front");
}
