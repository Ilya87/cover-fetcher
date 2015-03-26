#ifndef ITEMVIEW_H
#define ITEMVIEW_H

#include "interfaces/itemviewplugin.h"
#include "ui_config.h"

class CoverFetcher;

/**
 * \brief       Fetch covers using MusicBrainz.
 * \details		This plugin is the first plugin for MiamPlayer which goes on the web to do a specific job: fetching missing covers.
 *		It is more a proof-of-concept than a real plugin even though it's working. Interfaces are intended to be generic but it's
 *		difficult to make perfect interfaces when you only have written one plugin. Moreover, fetching covers using MusicBrainz' webservice
 *		is kind hard because string matching is a complex problem. In the future, other webservices could be added without too much effort.
 * \author      Matthieu Bachelier
 * \version     0.6
 * \copyright   GNU General Public License v3
 */
class ItemView : public QObject, public ItemViewPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID ItemViewPlugin_iid)
	Q_INTERFACES(ItemViewPlugin)

private:
	QMap<QString, CoverFetcher*> _coverFetchers;

	Ui::ConfigForm _ui;

public:
	explicit ItemView();

	virtual ~ItemView();

	/// From BasicPlugin
	virtual QWidget *configPage();

	inline virtual bool isConfigurable() const { return true; }

	inline virtual QString name() const { return "CoverFetcher"; }

	inline virtual QString version() const { return "0.6"; }

	/// From ItemViewPlugin
	virtual QStringList classesToExtend();

	virtual QAction * action(const QString & /*view*/, QMenu * /*parent*/);

	virtual void setSelectedTracksModel(const QString &view, SelectedTracksModel *selectedTracksModel);
};

#endif // ITEMVIEW_H
