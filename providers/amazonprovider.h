#ifndef AMAZONPROVIDER_H
#define AMAZONPROVIDER_H

#include "coverartprovider.h"

class MIAMCORE_LIBRARY AmazonProvider : public CoverArtProvider
{
	Q_OBJECT
private:
	// Amazon has a web crawler that looks for access keys in public source code,
	// so we apply some encryption to these keys.
	static const char* accessKeyB64;
	static const char* secretAccessKeyB64;
	static const char* url;
	static const char* associateTag;

public:
	explicit AmazonProvider(QObject *parent = nullptr);

	virtual QUrl query(const QString &expr) override;

	virtual QUrl album(const QString &expr) override;

private:
	static QByteArray hmac(const QByteArray &key, const QByteArray &data);
};

#endif // AMAZONPROVIDER_H
