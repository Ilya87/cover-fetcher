#ifndef COVERWIDGETITEMDELEGATE_H
#define COVERWIDGETITEMDELEGATE_H

#include <QListWidget>
#include <QStyledItemDelegate>

class CoverWidgetItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT
private:
	QListWidget *_listWidget;

public:
	explicit CoverWidgetItemDelegate(QListWidget *parent);

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // COVERWIDGETITEMDELEGATE_H
