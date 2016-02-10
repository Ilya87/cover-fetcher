#include "fetchdialog.h"

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

FetchDialog::FetchDialog(const QList<CoverArtProvider *> &providers, QWidget *parent)
	: QDialog(parent, Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)
{
	this->setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);

	// Change UI
	connect(previewSizeSlider, &QSlider::valueChanged, this, &FetchDialog::updateCoverSize);

	Settings *settings = Settings::instance();

	// Setting the value will trigger valueChanged connected upthere on purpose
	previewSizeSlider->setValue(settings->value("CoverFetcher/previewSizeSliderValue", 0).toInt());
	restoreGeometry(settings->value("CoverFetcher/geometry").toByteArray());

	// Filter on apply button only
	connect(buttonBox, &QDialogButtonBox::clicked, this, [=](QAbstractButton *button) {
		if (QDialogButtonBox::ApplyRole == buttonBox->buttonRole(button)) {
			this->applyChanges();
		}
		this->deleteLater();
	});

	for (CoverArtProvider *coverArtProvider : providers) {
		connect(coverArtProvider, &CoverArtProvider::aboutToCreateCover, this, &FetchDialog::addCover);
	}
}

FetchDialog::~FetchDialog()
{

}

void FetchDialog::closeEvent(QCloseEvent *)
{
	Settings::instance()->setValue("CoverFetcher/geometry", saveGeometry());
}

bool FetchDialog::integrateCoverToFile(Cover *cover, QString artistId, QString albumId)
{
	SqlDatabase db;
	db.open();

	QSqlQuery findTracks(db);
	findTracks.prepare("SELECT uri FROM tracks WHERE artistId = ? AND albumId = ?");
	findTracks.addBindValue(artistId);
	findTracks.addBindValue(albumId);
	bool b = findTracks.exec();
	while (findTracks.next()) {
		FileHelper fh(findTracks.record().value(0).toString());
		fh.setCover(cover);
		if (fh.save()) {
			qDebug() << "Cover has been successfully integrated into file" << fh.fileInfo().absoluteFilePath();
		} else {
			qDebug() << "Cover wasn't integrated into file" << fh.fileInfo().absoluteFilePath();
		}
	}

	QSqlQuery updateTracks(db);
	updateTracks.prepare("UPDATE tracks SET internalCover = 1 WHERE artistId = ? AND albumId = ?");
	updateTracks.addBindValue(artistId);
	updateTracks.addBindValue(albumId);
	b = updateTracks.exec();

	return b;
}

void FetchDialog::addCover(const QString &album, const QByteArray &coverByteArray)
{
	qDebug() << Q_FUNC_INFO << album;
	for (QGroupBox *gb : findChildren<QGroupBox*>("albumCoverGroupBox")) {

		qDebug() << Q_FUNC_INFO << gb->layout()->sizeConstraint();
		if (gb->title() == album) {
			QListWidget *list = gb->findChild<QListWidget*>("remoteCovers");
			QListWidgetItem *item = new QListWidgetItem(list);
			item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
			item->setCheckState(Qt::Unchecked);

			QPixmap pixmap;
			pixmap.loadFromData(coverByteArray);
			item->setIcon(QIcon(pixmap));
			item->setData(LW_CoverData, coverByteArray);
			break;
		}
	}
}

void FetchDialog::applyChanges()
{
	bool integrateCoverToFiles = Settings::instance()->value("CoverFetcher/integrateCoverToFiles").toBool();

	for (QGroupBox *gb : this->findChildren<QGroupBox*>("albumCoverGroupBox")) {
		QListWidget *currentCoverList = gb->findChild<QListWidget*>("currentCover");
		QString artistId = currentCoverList->item(0)->data(LW_Artist).toString();
		QString albumId = currentCoverList->item(0)->data(LW_Album).toString();

		// Right now, there's only one cover per album (one remote location)! So one can check at most 1 item...
		QListWidget *remoteCoverList = gb->findChild<QListWidget*>("remoteCovers");
		for (int i = 0; i < remoteCoverList->count(); i++) {

			// Convenient way to get data
			QListWidgetItem *item = remoteCoverList->item(i);
			Cover *c = new Cover(item->data(LW_CoverData).toByteArray());
			if (item->checkState() == Qt::Checked) {

				// Create inner cover for each file
				if (integrateCoverToFiles) {

					// Before creating the cover, we have to know which file to process
					bool b = this->integrateCoverToFile(c, artistId, albumId);
					qDebug() << "updating tracks" << b;
				} else {
					/// TODO
				}
				break;
			}
		}
	}
	this->close();
	emit refreshView();
}

void FetchDialog::updateCoverSize(int value)
{
	int size;
	switch (value) {
	case 0:
		size = 100;
		break;
	case 1:
		size = 250;
		break;
	case 2:
		size = 500;
		break;
	}

	Settings *settings = Settings::instance();
	settings->setValue("CoverFetcher/coverValueSize", size);
	settings->setValue("CoverFetcher/previewSizeSliderValue", value);
	previewSizeValue->setText(QString(tr("%1px")).arg(size));
	QSize iconSize(size, size);
	for (QListWidget *listWidget : this->findChildren<QListWidget*>()) {
		listWidget->setMinimumHeight(size + 10);
		listWidget->setMaximumHeight(size + 10);
		if (listWidget->objectName() == "currentCover") {
			listWidget->setMinimumWidth(size + 10);
			listWidget->setMaximumWidth(size + 10);
		} else {
			listWidget->setMinimumWidth(size + 10);
		}
		listWidget->setIconSize(iconSize);
		qDebug() << Q_FUNC_INFO << listWidget->parent();
	}
}
