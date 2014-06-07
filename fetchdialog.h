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
	//int *_coverValueSize;

	Q_ENUMS(ListWidgetUserType)

public:
	explicit FetchDialog(QWidget *parent = 0);

	enum ListWidgetUserType { LW_Artist			= Qt::UserRole + 1,
							  LW_Album			= Qt::UserRole + 2,
							  LW_TmpCoverPath	= Qt::UserRole + 3};

	//inline int coverValueSize() const { return *_coverValueSize; }

protected:
	void closeEvent(QCloseEvent *e);

private:
	void clear();

private slots:
	void applyChanges();

	void updateCoverSize(int value);

signals:
	void refreshView();
};

#endif // FETCHDIALOG_H
