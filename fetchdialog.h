#ifndef FETCHDIALOG_H
#define FETCHDIALOG_H

#include <QDialog>

#include "ui_fetchdialog.h"

class FetchDialog : public QDialog, public Ui::FetchDialog
{
	Q_OBJECT
private:
	int _coverValueSize;

public:
	explicit FetchDialog(QWidget *parent = 0);

	inline int coverValueSize() const { return _coverValueSize; }

private slots:
	void updateCoverSize(int value);
};

#endif // FETCHDIALOG_H
