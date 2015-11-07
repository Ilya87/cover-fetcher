#include "musicbrainzprovider.h"

#include <QGroupBox>
#include <QXmlStreamReader>

#include <QtDebug>

MusicBrainzProvider::MusicBrainzProvider(QObject *parent)
	: CoverArtProvider(parent)
{}

QUrl MusicBrainzProvider::query(const QString &artistId)
{
	return QUrl("http://musicbrainz.org/ws/2/release-group/?query=artist:%22" + artistId + "%22;limit=100");
}

QUrl MusicBrainzProvider::album(const QString &albumId)
{
	return QUrl("http://coverartarchive.org/release-group/" + albumId + "/front");
}

void MusicBrainzProvider::fetchReleases(const QByteArray &ba)
{
	QXmlStreamReader xml(ba);

	// Album Text -> Album ID
	QMap<QString, QString> map;
	while(!xml.atEnd() && !xml.hasError()) {

		QXmlStreamReader::TokenType token = xml.readNext();

		// Parse start elements
		if (token == QXmlStreamReader::StartElement) {
			if (xml.name() == "release-group") {
				if (xml.attributes().hasAttribute("id")) {
					QStringRef sr = xml.attributes().value("id");
					if (xml.readNextStartElement() && xml.name() == "title") {
						map.insert(xml.readElementText().toLower(), sr.toString());
					}
				}
			}
		}
	}

	QMapIterator<QString, QString> it(map);
	/// Complexity: should be improved!
	while (it.hasNext()) {
		it.next();
		//qDebug() << "while:" << it.key() << it.value();
		/*for (QGroupBox *gb : _fetchDialog->findChildren<QGroupBox*>()) {
			if (uiLevenshteinDistance(gb->title().toLower().toStdString(), it.key().toStdString()) < 4 ||
					it.key().contains(gb->title().toLower()) || gb->title().toLower().contains(it.key())) {
				//qDebug() << "uiLevenshteinDistance: get the covert art for " << gb->title() << it.key() << it.value();
				/// FIXME: find a way to get the 500px thumbnail and to automatically download the large one after
				for (CoverArtProvider *provider : _providers) {
					QUrl url = provider->album(it.value());
					QNetworkRequest request(url);
					request.setHeader(QNetworkRequest::UserAgentHeader, "MiamPlayer/0.8.0 ( http://www.miam-player.org/ )" );
					_releasesGroup.insert(url, gb->title());
					QNetworkReply *reply = _manager->get(request);
					_currentCalls.insert(reply->url(), FO_DownloadCover);
				}
				//it.remove();
				break;
			}
		}*/
	}
}
