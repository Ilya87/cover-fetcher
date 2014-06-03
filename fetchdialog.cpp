#include "fetchdialog.h"
#include "settings.h"
#include "sqldatabase.h"

#include <QGroupBox>
#include <QListWidget>
#include <QScrollBar>
#include <QSqlQuery>

#include <QtDebug>

FetchDialog::FetchDialog(QWidget *parent) :
	QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)
{
	this->setupUi(this);

	connect(previewSizeSlider, &QSlider::valueChanged, this, &FetchDialog::updateCoverSize);

	Settings *settings = Settings::getInstance();
	settings->beginGroup("CoverFetcher");
	_coverValueSize = settings->value("coverValueSize", 64).toInt();

	// Setting the value will trigger valueChanged connected upthere on purpose
	previewSizeSlider->setValue(settings->value("previewSizeSliderValue", 1).toInt());
	restoreGeometry(settings->value("geometry").toByteArray());
	settings->endGroup();

	connect(this, &QDialog::finished, this, [=]() {
		settings->beginGroup("CoverFetcher");
		settings->setValue("geometry", saveGeometry());
		settings->endGroup();
	});

	connect(buttonBox, &QDialogButtonBox::clicked, this, [=](QAbstractButton *button) {
		if (QDialogButtonBox::ApplyRole == buttonBox->buttonRole(button)) {
			this->applyChanges();
		}
	});
}

void FetchDialog::closeEvent(QCloseEvent *)
{
	QLayoutItem *child;
	while ((child = scrollAreaWidgetContents->layout()->takeAt(0)) != 0) {
		if (child->widget()) {
			qDebug() << child->widget();
			delete child->widget();
		}
		delete child;
	}
	scrollArea->verticalScrollBar()->setValue(0);
}

#include "filehelper.h"

void FetchDialog::applyChanges()
{
	Settings *settings = Settings::getInstance();
	settings->beginGroup("CoverFetcher");
	bool integrateCoverToFiles = settings->value("integrateCoverToFiles").toBool();
	settings->endGroup();

	SqlDatabase db;
	db.open();
	// TABLE tracks (artist varchar(255), artistAlbum varchar(255), album varchar(255),
	//				title varchar(255), trackNumber INTEGER, discNumber INTEGER, year INTEGER,
	//				absPath varchar(255) PRIMARY KEY ASC, path varchar(255),
	//				coverAbsPath varchar(255), internalCover INTEGER DEFAULT 0, externalCover INTEGER DEFAULT 0)

	foreach (QListWidget *listWidget, this->findChildren<QListWidget*>("remoteCovers")) {
		for (int i = 0; i < listWidget->count(); i++) {
			if (listWidget->item(i)->checkState() == Qt::Checked) {
				QGroupBox *gb = qobject_cast<QGroupBox*>(listWidget->parent());
				qDebug() << "update tracks for album" << gb->title();
				QSqlQuery updateTracks(db);
				if (integrateCoverToFiles) {
					updateTracks.prepare("UPDATE tracks SET internalCover = 1 WHERE artist = :artist AND album = :album");
					updateTracks.addBindValue("artist");
					updateTracks.addBindValue("album");
					/// TODO add cover
					FileHelper fh(filePath);
					Cover c();
					fh.setCover(&c);
				} else {
					updateTracks.prepare("UPDATE tracks SET coverAbsPath");
				}
				if (updateTracks.exec()) {

				}
				qDebug() << "find album path, create jpg or insert raw bytes in audio files";
				break;
			}
		}
	}
	db.close();
	qDebug() << "then tell the library to refresh selected nodes";
	this->close();
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
	settings->beginGroup("CoverFetcher");
	settings->setValue("coverValueSize", _coverValueSize);
	settings->setValue("previewSizeSliderValue", value);
	settings->endGroup();
	previewSizeValue->setText(QString("%1px").arg(_coverValueSize));
	QSize iconSize(_coverValueSize, _coverValueSize);
	foreach (QListWidget *listWidget, this->findChildren<QListWidget*>()) {
		listWidget->setIconSize(iconSize);
		listWidget->setMinimumHeight(_coverValueSize + 10);
		listWidget->setMaximumHeight(_coverValueSize + 10);
		//if (listWidget->objectName() == "currentCover") {
		listWidget->setMinimumWidth(_coverValueSize + 10);
		listWidget->setMaximumWidth(_coverValueSize + 10);
		//}
	}
}
