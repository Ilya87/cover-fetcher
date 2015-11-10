#include "amazonprovider.h"

#include <QCryptographicHash>
#include <QDateTime>
#include <QUrlQuery>

#include <QtDebug>

// Amazon has a web crawler that looks for access keys in public source code, so we apply some encryption to these keys.
const char* AmazonProvider::accessKeyB64 = "QUtJQUpHUVVVSFREVlBORTdOUkE=";
const char* AmazonProvider::secretAccessKeyB64 = "UHk3NEdma1kxQm1rQmU3UldjL0VyN2dUSk9TVlFyK2NrWGxoYVJwVw==";
const char* AmazonProvider::url = "http://ecs.amazonaws.com/onca/xml";
const char* AmazonProvider::associateTag = "miam-player";

AmazonProvider::AmazonProvider(QNetworkAccessManager *parent)
	: CoverArtProvider(parent)
{

}

QUrl AmazonProvider::query(const QString &artist, const QString &album)
{
	typedef QPair<QString, QString> Arg;
	typedef QList<Arg> ArgList;

	typedef QPair<QByteArray, QByteArray> EncodedArg;
	typedef QList<EncodedArg> EncodedArgList;

	// Must be sorted by Parameter/Value pair in byte (=ASCII here) value AW... < As... < Ke... < Op...
	ArgList args = ArgList() << Arg("AWSAccessKeyId", QByteArray::fromBase64(accessKeyB64))
							 << Arg("AssociateTag", associateTag)
							 << Arg("Keywords", artist + "%20" + album)
							 << Arg("Operation", "ItemSearch")
							 << Arg("ResponseGroup", "Images")
							 << Arg("SearchIndex", "Music")
							 << Arg("Service", "AWSECommerceService")
							// << Arg("Sort", "titlerank")
							 << Arg("Timestamp", QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss.zzzZ"))
							 << Arg("Version", "2013-08-01");

	EncodedArgList encoded_args;
	QStringList queryItems;

	// Encode the arguments
	QUrlQuery urlQuery;
	for (const Arg& arg : args) {
		EncodedArg encoded_arg(QUrl::toPercentEncoding(arg.first), QUrl::toPercentEncoding(arg.second));
		encoded_args << encoded_arg;
		queryItems << QString(encoded_arg.first + "=" + encoded_arg.second);
		urlQuery.addQueryItem(arg.first, arg.second);
	}

	// Sign the request
	QUrl u(url);

	QByteArray dataToSign = QString("GET\n%1\n%2\n%3")
			.arg(u.host(), u.path(), queryItems.join("&"))
			.toLatin1();

	QByteArray signature(AmazonProvider::hmac(QByteArray::fromBase64(secretAccessKeyB64), dataToSign));

	// Add the signature to the request
	urlQuery.addQueryItem("Signature", QUrl::toPercentEncoding(signature.toBase64()));
	u.setQuery(urlQuery);
	return u;
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
		//qDebug() << Q_FUNC_INFO << "ByteArray" << ba;
	}
		break;
	default:
		qDebug() << Q_FUNC_INFO << "Default?" << reply->url();
		break;
	}
}
