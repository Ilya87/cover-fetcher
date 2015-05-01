#include "fetchdialog.h"

#include "cover.h"
#include "filehelper.h"
#include "settings.h"
#include "model/sqldatabase.h"

#include <QAbstractButton>
#include <QGroupBox>
#include <QListWidget>
#include <QScrollBar>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QtDebug>

FetchDialog::FetchDialog(QWidget *parent) :
	QDialog(parent)
{
	this->setupUi(this);

	// Change UI
	connect(previewSizeSlider, &QSlider::valueChanged, this, &FetchDialog::updateCoverSize);

	Settings *settings = Settings::instance();

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

	Settings::instance()->setValue("CoverFetcher/geometry", saveGeometry());
}

void FetchDialog::applyChanges()
{
	bool integrateCoverToFiles = Settings::instance()->value("CoverFetcher/integrateCoverToFiles").toBool();

	SqlDatabase *db = SqlDatabase::instance();
	//db->open();

	for (QGroupBox *gb : this->findChildren<QGroupBox*>("albumCoverGroupBox")) {
		QListWidget *currentCoverList = gb->findChild<QListWidget*>("currentCover");
		QString artistId = currentCoverList->item(0)->data(LW_Artist).toString();
		QString albumId = currentCoverList->item(0)->data(LW_Album).toString();

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
					QSqlQuery findTracks(*db);
					findTracks.prepare("SELECT uri FROM tracks WHERE artistId = ? AND albumId = ?");
					findTracks.addBindValue(artistId);
					findTracks.addBindValue(albumId);
					bool b = findTracks.exec();
					qDebug() << "selecting tracks to update" << b << artistId << albumId;
					while (findTracks.next()) {
						FileHelper fh(findTracks.record().value(0).toString());
						fh.setCover(&c);
						b = fh.save();
						qDebug() << "writing cover into file" << b << fh.title();
					}

					QSqlQuery updateTracks(*db);
					updateTracks.prepare("UPDATE tracks SET internalCover = 1 WHERE artistId = ? AND albumId = ?");
					updateTracks.addBindValue(artistId);
					updateTracks.addBindValue(albumId);
					b = updateTracks.exec();
					qDebug() << "updating tracks" << b;
				}
				break;
			}
		}
	}
	//db->close();
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

	Settings *settings = Settings::instance();
	settings->setValue("CoverFetcher/coverValueSize", size);
	settings->setValue("CoverFetcher/previewSizeSliderValue", value);
	previewSizeValue->setText(QString(tr("%1px")).arg(size));
	QSize iconSize(size, size);
	for (QListWidget *listWidget : this->findChildren<QListWidget*>()) {
		listWidget->setIconSize(iconSize);
		listWidget->setMinimumHeight(size + 10);
		listWidget->setMaximumHeight(size + 10);
		//if (listWidget->objectName() == "currentCover") {
		listWidget->setMinimumWidth(size + 10);
		listWidget->setMaximumWidth(size + 10);
		//}
	}
}
