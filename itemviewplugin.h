#ifndef ITEMVIEWPLUGIN_H
#define ITEMVIEWPLUGIN_H

#include "itemviewplugininterface.h"
#include "ui_config.h"

class CoverFetcher;

/**
 * \brief       Fetch covers using MusicBrainz
 * \author      Matthieu Bachelier
 * \version     0.4
 * \copyright   GNU General Public License v3
 */
class ItemViewPlugin : public QObject, public ItemViewPluginInterface
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID ItemViewPluginInterface_iid)
	Q_INTERFACES(ItemViewPluginInterface)

private:
	QMap<QString, CoverFetcher*> _coverFetchers;

	Ui::ConfigForm _ui;

public:
	explicit ItemViewPlugin();

	virtual ~ItemViewPlugin();

	/// From BasicPluginInterface
	virtual QWidget *configPage();

	inline virtual bool isConfigurable() const { return true; }

	inline virtual QString name() const { return "CoverFetcher"; }

	inline virtual QString version() const { return "0.4"; }

	/// From ItemViewPluginInterface
	virtual QStringList classesToExtend();

	virtual QAction * action(const QString & /*view*/, QMenu * /*parent*/);

	virtual void setSelectedTracksModel(const QString &view, SelectedTracksModel *selectedTracksModel);
};

#endif // ITEMVIEWPLUGIN_H
