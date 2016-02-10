#ifndef COVERFETCHERPLUGIN_H
#define COVERFETCHERPLUGIN_H

#include "providers/coverartprovider.h"
#include "interfaces/itemviewplugin.h"
#include "ui_config.h"

/**
 * \brief       Fetch covers using MusicBrainz.
 * \details		This plugin is the first plugin for MiamPlayer which goes on the web to do a specific job: fetching missing covers.
 *		It is more a proof-of-concept than a real plugin even though it's working. Interfaces are intended to be generic but it's
 *		difficult to make perfect interfaces when you only have written one plugin. Moreover, fetching covers using MusicBrainz' webservice
 *		is kind hard because string matching is a complex problem. In the future, other webservices could be added without too much effort.
 * \author      Matthieu Bachelier
 * \version     0.8
 * \copyright   GNU General Public License v3
 */
class MIAMCORE_LIBRARY CoverFetcherPlugin : public ItemViewPlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID ItemViewPlugin_iid)
	Q_INTERFACES(ItemViewPlugin)

private:
	Ui::ConfigForm _ui;
	QMap<QString, SelectedTracksModel*> _viewModels;

	QList<CoverArtProvider*> _providers;
	QNetworkAccessManager *_manager;

public:
	explicit CoverFetcherPlugin(QObject *parent = nullptr);

	virtual ~CoverFetcherPlugin();

	/// From BasicPlugin
	/** Generate UI in lazy loading mode. */
	virtual QWidget *configPage() override;

	inline virtual bool isConfigurable() const override { return true; }

	inline virtual QString name() const override { return "CoverFetcher"; }

	inline virtual QString version() const override { return "0.7"; }

	/// From ItemViewPlugin
	virtual QStringList classesToExtend() override;

	virtual QAction * action(const QString & /*view*/, QMenu * /*parent*/) override;

	virtual void setSelectedTracksModel(const QString &view, SelectedTracksModel *selectedTracksModel) override;

private:
	void fetch(SelectedTracksModel *selectedTracksModel);

	/** When one is checking items in the list, providers are added or removed dynamically. */
	void manageProvider(bool enabled, QCheckBox *checkBox);
};

#endif // COVERFETCHERPLUGIN_H
