#ifndef AMAZONPROVIDER_H
#define AMAZONPROVIDER_H

#include "coverartprovider.h"

class MIAMCORE_LIBRARY AmazonProvider : public CoverArtProvider
{
	Q_OBJECT
private:
	// Amazon has a web crawler that looks for access keys in public source code, so we apply some encryption to these keys.
	static const char* accessKeyB64;
	static const char* secretAccessKeyB64;
	static const char* host;
	static const char* associateTag;

public:
	explicit AmazonProvider(QNetworkAccessManager *parent);

	virtual QUrl query(const QString &artist, const QString &album) override;

	virtual QUrl album(const QString &expr) override;

	inline virtual ProviderType type() override { return PT_Amazon; }

private:
	/** Request must be signed with Keyed-hash Message Authentication Code and SHA-256. */
	static QByteArray hmac(const QByteArray &key, const QByteArray &data);

	void parseSearchResults(const QString &album, const QByteArray &ba);

public slots:
	virtual void dispatchReply(QNetworkReply *reply) override;
};

#endif // AMAZONPROVIDER_H
