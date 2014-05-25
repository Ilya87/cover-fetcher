#include "fetchdialog.h"
#include "settings.h"

#include <QListWidget>

FetchDialog::FetchDialog(QWidget *parent) :
	QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)
{
	this->setupUi(this);

	connect(previewSizeSlider, &QSlider::valueChanged, this, &FetchDialog::updateCoverSize);

	Settings *settings = Settings::getInstance();
	settings->beginGroup("PluginCoverFetcher");
	_coverValueSize = settings->value("coverValueSize", 64).toInt();

	// Setting the value will trigger valueChanged connected upthere on purpose
	previewSizeSlider->setValue(settings->value("previewSizeSliderValue", 1).toInt());
	restoreGeometry(settings->value("geometry").toByteArray());
	settings->endGroup();

	connect(this, &QDialog::finished, [=]() {
		settings->beginGroup("PluginCoverFetcher");
		settings->setValue("geometry", saveGeometry());
		settings->endGroup();
	});
}

void FetchDialog::updateCoverSize(int value)
{
	switch (value) {
	case 0:
		_coverValueSize = 32;
		break;
	default:
	case 1:
		_coverValueSize = 64;
		break;
	case 2:
		_coverValueSize = 100;
		break;
	case 3:
		_coverValueSize = 250;
		break;
	case 4:
		_coverValueSize = 500;
		break;
	}

	Settings *settings = Settings::getInstance();
	settings->beginGroup("PluginCoverFetcher");
	settings->setValue("coverValueSize", _coverValueSize);
	settings->setValue("previewSizeSliderValue", value);
	settings->endGroup();
	previewSizeValue->setText(QString("%1px").arg(_coverValueSize));
	QSize iconSize(_coverValueSize, _coverValueSize);
	foreach (QListWidget *listWidget, this->findChildren<QListWidget*>()) {
		listWidget->setIconSize(iconSize);
		listWidget->setMinimumHeight(_coverValueSize + 10);
		listWidget->setMaximumHeight(_coverValueSize + 10);
		if (listWidget->objectName() == "currentCover") {
			listWidget->setMinimumWidth(_coverValueSize + 10);
			listWidget->setMaximumWidth(_coverValueSize + 10);
		}
	}
}
