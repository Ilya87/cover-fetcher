#include "amazonprovider.h"

#include <QCryptographicHash>
#include <QDateTime>
#include <QUrlQuery>

#include <QtDebug>

// Amazon has a web crawler that looks for access keys in public source code, so we apply some encryption to these keys.
const char* AmazonProvider::accessKeyB64 = "QUtJQUpHUVVVSFREVlBORTdOUkE=";
const char* AmazonProvider::secretAccessKeyB64 = "UHk3NEdma1kxQm1rQmU3UldjL0VyN2dUSk9TVlFyK2NrWGxoYVJwVw==";
const char* AmazonProvider::host = "http://ecs.amazonaws.com/onca/xml";
const char* AmazonProvider::associateTag = "miam-player";

AmazonProvider::AmazonProvider(QNetworkAccessManager *parent)
	: CoverArtProvider(parent)
{}

QUrl AmazonProvider::query(const QString &artist, const QString &album)
{
	// Encode the arguments
	QUrlQuery urlQuery;
	urlQuery.addQueryItem("AWSAccessKeyId", QByteArray::fromBase64(accessKeyB64));
	urlQuery.addQueryItem("AssociateTag", associateTag);
	urlQuery.addQueryItem("Keywords", artist + " " + album);
	urlQuery.addQueryItem("Operation", "ItemSearch");
	urlQuery.addQueryItem("ResponseGroup", "Images");
	urlQuery.addQueryItem("SearchIndex", "Music");
	urlQuery.addQueryItem("Service", "AWSECommerceService");
	QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss.zzzZ");
	urlQuery.addQueryItem("Timestamp", timestamp);
	urlQuery.addQueryItem("Version", "2013-08-01");

	// Sign the request
	QUrl url(host);

	QByteArray dataToSign = QString("GET\n%1\n%2\n%3")
			.arg(url.host(), url.path(), urlQuery.toString())
			.toLatin1();

	qDebug() << Q_FUNC_INFO << urlQuery.toString();

	QByteArray signature(AmazonProvider::hmac(QByteArray::fromBase64(secretAccessKeyB64), dataToSign));

	// Add the signature to the request
	urlQuery.addQueryItem("Signature", QUrl::toPercentEncoding(signature.toBase64()));
	url.setQuery(urlQuery);
	return url;
}

QUrl AmazonProvider::album(const QString &expr)
{
	return QUrl("http://ecs.amazonaws.com/onca/xml?album=" + expr);
}


QByteArray AmazonProvider::hmac(const QByteArray &key, const QByteArray &data) {
	static int blockSize = 64;

	QByteArray innerPadding(blockSize, static_cast<char>(0x36));
	QByteArray outerPadding(blockSize, static_cast<char>(0x5c));
	for (int i = 0; i < key.length(); i++) {
		innerPadding[i] = innerPadding[i] ^ key[i];
		outerPadding[i] = outerPadding[i] ^ key[i];
	}

	return QCryptographicHash::hash(outerPadding + QCryptographicHash::hash(innerPadding + data, QCryptographicHash::Sha256), QCryptographicHash::Sha256);
}

void AmazonProvider::dispatchReply(QNetworkReply *reply)
{
	// Dispatch request
	Fetch_Operations fo = (Fetch_Operations)reply->property("requestType").toInt();
	switch (fo) {
	case FO_GetReleases:
		qDebug() << Q_FUNC_INFO << "Current fetch operation GetReleases" << reply->url();
		break;
	case FO_DownloadCover:
		qDebug() << Q_FUNC_INFO << "Current fetch operation DownloadCover" << reply->url();
		break;
	case FO_Search: {
		qDebug() << Q_FUNC_INFO << "Current fetch operation Search" << reply->url();
		QByteArray ba = reply->readAll();
		qDebug() << Q_FUNC_INFO << "ByteArray" << ba;
	}
		break;
	default:
		qDebug() << Q_FUNC_INFO << "Default?" << reply->url();
		break;
	}
}
