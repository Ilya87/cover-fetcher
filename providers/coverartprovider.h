#ifndef COVERARTPROVIDER_H
#define COVERARTPROVIDER_H

#include <QObject>
#include <QUrl>

#include "miamcore_global.h"

/**
 * \brief		The CoverArtProvider class is an abstract class for registering various webservices.
 * \author      Matthieu Bachelier
 * \copyright   GNU General Public License v3
 */
class MIAMCORE_LIBRARY CoverArtProvider : public QObject
{
	Q_OBJECT
public:
	explicit CoverArtProvider(QObject *parent = nullptr) : QObject(parent) {}

	virtual ~CoverArtProvider() {}

	virtual QUrl query(const QString &) = 0;

	virtual QUrl album(const QString &) = 0;
};

#endif // COVERARTPROVIDER_H
