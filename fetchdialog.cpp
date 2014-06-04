#include "fetchdialog.h"

#include "cover.h"
#include "filehelper.h"
#include "settings.h"
#include "sqldatabase.h"

#include <QGroupBox>
#include <QListWidget>
#include <QScrollBar>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QtDebug>

FetchDialog::FetchDialog(QWidget *parent) :
	QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)
{
	this->setupUi(this);

	// Change UI
	connect(previewSizeSlider, &QSlider::valueChanged, this, &FetchDialog::updateCoverSize);

	Settings *settings = Settings::getInstance();
	settings->beginGroup("CoverFetcher");
	_coverValueSize = settings->value("coverValueSize", 64).toInt();

	// Setting the value will trigger valueChanged connected upthere on purpose
	previewSizeSlider->setValue(settings->value("previewSizeSliderValue", 1).toInt());
	restoreGeometry(settings->value("geometry").toByteArray());
	settings->endGroup();

	// Filter on apply button only
	connect(buttonBox, &QDialogButtonBox::clicked, this, [=](QAbstractButton *button) {
		if (QDialogButtonBox::ApplyRole == buttonBox->buttonRole(button)) {
			this->applyChanges();
		}
		this->clear();
	});
}

void FetchDialog::closeEvent(QCloseEvent *)
{
	this->clear();
}

void FetchDialog::clear()
{
	QLayoutItem *child;
	while ((child = scrollAreaWidgetContents->layout()->takeAt(0)) != 0) {
		if (child->widget()) {
			delete child->widget();
		}
		delete child;
	}
	scrollArea->verticalScrollBar()->setValue(0);

	Settings *settings = Settings::getInstance();
	settings->beginGroup("CoverFetcher");
	settings->setValue("geometry", saveGeometry());
	settings->endGroup();
}

void FetchDialog::applyChanges()
{
	Settings *settings = Settings::getInstance();
	settings->beginGroup("CoverFetcher");
	bool integrateCoverToFiles = settings->value("integrateCoverToFiles").toBool();
	settings->endGroup();

	SqlDatabase db;
	db.open();

	foreach (QGroupBox *gb, this->findChildren<QGroupBox*>("albumCoverGroupBox")) {
		QListWidget *currentCoverList = gb->findChild<QListWidget*>("currentCover");
		QString artist = currentCoverList->item(0)->data(LW_Artist).toString();
		QString album = currentCoverList->item(0)->data(LW_Album).toString();

		// Right now, there's only one cover per album (one remote location)! So one can check at most 1 item...
		QListWidget *remoteCoverList = gb->findChild<QListWidget*>("remoteCovers");
		for (int i = 0; i < remoteCoverList->count(); i++) {
			QListWidgetItem *item = remoteCoverList->item(i);

			// Convenient way to get data
			Cover c(item->data(LW_TmpCoverPath).toString());
			if (item->checkState() == Qt::Checked) {

				// Create inner cover for each file
				if (integrateCoverToFiles) {

					// Before creating the cover, we have to know which file to process
					QSqlQuery findTracks(db);
					findTracks.prepare("SELECT absPath FROM tracks WHERE artist = :artist AND album = :album");
					findTracks.addBindValue(artist);
					findTracks.addBindValue(album);
					findTracks.exec();
					while (findTracks.next()) {
						FileHelper fh(findTracks.record().value(0).toString());
						fh.setCover(&c);
						fh.save();
					}

					QSqlQuery updateTracks(db);
					updateTracks.prepare("UPDATE tracks SET internalCover = 1 WHERE artist = :artist AND album = :album");
					updateTracks.addBindValue(artist);
					updateTracks.addBindValue(album);
					updateTracks.exec();
				}
				break;
			}
		}
	}
	db.close();
	this->close();
	emit refreshView();
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
