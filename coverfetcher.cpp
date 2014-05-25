#include "coverfetcher.h"
#include "sqldatabase.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStandardItemModel>

#include <QtDebug>

#include "ui_templateCover.h"

CoverFetcher::CoverFetcher(QObject *parent) :
	QObject(parent), _selectionModel(NULL)
{
	_fetchDialog = new FetchDialog;
}

QAction * CoverFetcher::action(QMenu *parentMenu)
{
	QAction *action = new QAction("Fetch covers", parentMenu);
	connect(action, &QAction::triggered, this, &CoverFetcher::fetch);
	return action;
}

void CoverFetcher::fetch()
{
	QLayoutItem *child;
	while ((child = _fetchDialog->scrollAreaWidgetContents->layout()->takeAt(0)) != 0) {
		if (child->widget()) {
			delete child->widget();
		}
		delete child;
	}

	SqlDatabase db;
	db.open();
	QList<QString> artists;
	foreach (QModelIndex index, _selectionModel->selectedIndexes()) {
		if (index.column() == 0) {
			//qDebug() << _selectionModel->model() << index.column();
			QVariant v = index.data(Qt::UserRole + 1);
			if (v.isValid()) {
				/// FIXME: Magic numbers from LibraryTreeView class
				switch (v.toInt()) {
				case 0: {
					qDebug() << "fetch covers for this artist" << index.data();
					artists.append(index.data().toString());
					break;
				}
				case 1:
					qDebug() << "fetch cover for this album" << index.data();
					break;
				default:
					break;
				}
			}
		}
	}

	// TABLE tracks (artist varchar(255), artistAlbum varchar(255), album varchar(255),
	//				title varchar(255), trackNumber INTEGER, discNumber INTEGER, year INTEGER,
	//				absPath varchar(255) PRIMARY KEY ASC, path varchar(255),
	//				coverAbsPath varchar(255), internalCover INTEGER DEFAULT 0, externalCover INTEGER DEFAULT 0)

	foreach (QString artist, artists) {

		QLabel *labelArtist = new QLabel("Artist: " + artist);
		_fetchDialog->scrollAreaWidgetContents->layout()->addWidget(labelArtist);

		QSqlQuery q(db);
		q.prepare("SELECT DISTINCT album, coverAbsPath FROM tracks WHERE artist = :artist ORDER BY year");
		q.bindValue(":artist", artist);
		if (q.exec()) {
			while (q.next()) {
				Ui_TemplateCovers templateCover;
				QWidget *covers = new QWidget;
				templateCover.setupUi(covers);
				// Fill the groupBox title with an Album from this Artist
				QString album = q.record().value(0).toString();
				templateCover.existingCoverGroupBox->setTitle(album);

				QSize s(_fetchDialog->coverValueSize(), _fetchDialog->coverValueSize());
				QSize s2(_fetchDialog->coverValueSize() + 10, _fetchDialog->coverValueSize() + 10);

				templateCover.currentCover->setDragDropMode(QListWidget::NoDragDrop);
				templateCover.currentCover->setIconSize(s);
				templateCover.currentCover->setMinimumSize(s2);
				templateCover.currentCover->setMaximumSize(s2);
				templateCover.remoteCovers->setDragDropMode(QListWidget::NoDragDrop);
				templateCover.remoteCovers->setIconSize(s);
				templateCover.remoteCovers->setMaximumHeight(s2.height());

				QListWidgetItem *currentCover = new QListWidgetItem();

				/// XXX: behold, internal covers are ignored
				if (!q.record().value(1).toString().isEmpty()) {
					currentCover->setIcon(QIcon(q.record().value(1).toString()));
				} else {
					currentCover->setIcon(QIcon(":/icons/disc"));
				}

				templateCover.currentCover->addItem(currentCover);
				_fetchDialog->scrollAreaWidgetContents->layout()->addWidget(covers);
			}
		}
	}
	QSpacerItem *vSpacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);
	_fetchDialog->scrollAreaWidgetContents->layout()->addItem(vSpacer);
	db.close();

	_fetchDialog->show();
	_fetchDialog->activateWindow();
}
