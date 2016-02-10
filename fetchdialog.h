#ifndef FETCHDIALOG_H
#define FETCHDIALOG_H

#include <QDialog>

#include "ui_fetchdialog.h"
#include "cover.h"
#include "providers/coverartprovider.h"

/**
 * \brief The FetchDialog class
 */
class FetchDialog : public QDialog, public Ui::FetchDialog
{
	Q_OBJECT
private:
	Q_ENUMS(ListWidgetUserType)

public:
	explicit FetchDialog(const QList<CoverArtProvider*> &providers, QWidget *parent = nullptr);

	virtual ~FetchDialog();

	enum ListWidgetUserType { LW_Artist		= Qt::UserRole + 1,
							  LW_Album		= Qt::UserRole + 2,
							  LW_CoverData	= Qt::UserRole + 3};

protected:
	virtual void closeEvent(QCloseEvent *e) override;

private:
	bool integrateCoverToFile(Cover *cover, QString artistId, QString albumId);

public slots:
	void addCover(const QString &album, const QByteArray &coverByteArray);

private slots:
	void applyChanges();

	void updateCoverSize(int value);

signals:
	void refreshView();
};

#endif // FETCHDIALOG_H
