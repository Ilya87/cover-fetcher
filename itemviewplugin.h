#ifndef ITEMVIEWPLUGIN_H
#define ITEMVIEWPLUGIN_H

#include "itemviewplugininterface.h"

class CoverFetcher;

/**
 * \brief       Fetch covers using MusicBrainz
 * \author      Matthieu Bachelier
 * \version     0.1
 * \copyright   GNU General Public License v3
 */
class ItemViewPlugin : public QObject, public ItemViewPluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID ItemViewPluginInterface_iid)
	Q_INTERFACES(ItemViewPluginInterface)

private:
	QMap<QString, CoverFetcher*> _coverFetchers;

public:
	explicit ItemViewPlugin();

	virtual ~ItemViewPlugin();

	/// From BasicPluginInterface
	virtual QWidget *configPage();

	inline virtual bool isConfigurable() const { return true; }

	inline virtual QString name() const { return "CoverFetcher"; }

	inline virtual QString version() const { return "0.3"; }

	/// From ItemViewPluginInterface
	virtual QStringList classesToExtend();

	virtual QAction * action(const QString & /*view*/, QMenu * /*parent*/);

	virtual void setSelectionModel(const QString &view, QItemSelectionModel *selectionModel);
};

#endif // ITEMVIEWPLUGIN_H
