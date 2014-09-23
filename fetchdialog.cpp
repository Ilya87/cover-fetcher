#include "fetchdialog.h"

#include "cover.h"
#include "filehelper.h"
#include "settings.h"
#include "sqldatabase.h"

#include <QAbstractButton>
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

	// Setting the value will trigger valueChanged connected upthere on purpose
	previewSizeSlider->setValue(settings->value("CoverFetcher/previewSizeSliderValue", 1).toInt());
	restoreGeometry(settings->value("CoverFetcher/geometry").toByteArray());

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

	Settings::getInstance()->setValue("CoverFetcher/geometry", saveGeometry());
}

void FetchDialog::applyChanges()
{
	bool integrateCoverToFiles = Settings::getInstance()->value("CoverFetcher/integrateCoverToFiles").toBool();

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
	int size;
	switch (value) {
	case 0:
		size = 32;
		break;
	default:
	case 1:
		size = 64;
		break;
	case 2:
		size = 100;
		break;
	case 3:
		size = 250;
		break;
	case 4:
		size = 500;
		break;
	}

	Settings *settings = Settings::getInstance();
	settings->setValue("CoverFetcher/coverValueSize", size);
	settings->setValue("CoverFetcher/previewSizeSliderValue", value);
	previewSizeValue->setText(QString(tr("%1px")).arg(size));
	QSize iconSize(size, size);
	foreach (QListWidget *listWidget, this->findChildren<QListWidget*>()) {
		listWidget->setIconSize(iconSize);
		listWidget->setMinimumHeight(size + 10);
		listWidget->setMaximumHeight(size + 10);
		//if (listWidget->objectName() == "currentCover") {
		listWidget->setMinimumWidth(size + 10);
		listWidget->setMaximumWidth(size + 10);
		//}
	}
}
