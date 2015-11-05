#ifndef FETCHDIALOG_H
#define FETCHDIALOG_H

#include <QDialog>

#include "ui_fetchdialog.h"

/**
 * \brief The FetchDialog class
 */
class FetchDialog : public QDialog, public Ui::FetchDialog
{
	Q_OBJECT
private:
	Q_ENUMS(ListWidgetUserType)

public:
	explicit FetchDialog(QWidget *parent = nullptr);

	enum ListWidgetUserType { LW_Artist			= Qt::UserRole + 1,
                              LW_Album			= Qt::UserRole + 2,
                              LW_TmpCoverPath	= Qt::UserRole + 3};

protected:
	virtual void closeEvent(QCloseEvent *e) override;

private:
	void clear();

private slots:
	void applyChanges();

	void updateCoverSize(int value);

signals:
	void refreshView();
};

#endif // FETCHDIALOG_H
