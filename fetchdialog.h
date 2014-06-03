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
	int _coverValueSize;

public:
	explicit FetchDialog(QWidget *parent = 0);

	inline int coverValueSize() const { return _coverValueSize; }

protected:
	void closeEvent(QCloseEvent *e);

private slots:
	void applyChanges();

	void updateCoverSize(int value);
};

#endif // FETCHDIALOG_H
