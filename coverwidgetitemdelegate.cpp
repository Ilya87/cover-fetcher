#include "coverwidgetitemdelegate.h"

#include <QApplication>
#include <QPainter>
#include <QStandardItemModel>

#include "settings.h"

#include <QtDebug>

CoverWidgetItemDelegate::CoverWidgetItemDelegate(QListWidget *parent)
	: QStyledItemDelegate(parent)
	, _listWidget(parent)
{
	if (_listWidget->objectName() == "remoteCovers") {
		connect(_listWidget, &QListWidget::itemClicked, this, [=](QListWidgetItem *item) {
			item->setCheckState(item->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked);
		});
	}
}

/** Redefined to display a checkbox in top-left corner. */
void CoverWidgetItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	// Draw only the border to keep the cover untouched
	if (option.state.testFlag(QStyle::State_Selected)) {
		painter->save();
		painter->setPen(option.palette.highlight().color());
		painter->drawRect(option.rect.adjusted(0, 0, -1, -1));
		painter->restore();
	}

	// Cover art
	QListWidgetItem *item = _listWidget->item(index.row());
	QRect cover(option.rect.x() + 1, option.rect.y() + 1, _listWidget->iconSize().width() - 1, _listWidget->iconSize().height() - 1);
	int v = Settings::instance()->value("CoverFetcher/coverValueSize", 64).toInt();
	//cover.translate(index.row() * v, 0);
	qDebug() << index.row() << index.column() << cover;

	QRect target(cover.topLeft(), QSize(v, v));
	//painter->translate(index.row() * v, 0);
	painter->drawPixmap(target, item->icon().pixmap(_listWidget->iconSize()), cover);

	// Checkbox
	if (_listWidget->objectName() == "remoteCovers") {
		QStyleOptionButton btn;
		btn.initFrom(_listWidget);
		btn.rect = QRect(option.rect.x() + 1, option.rect.y() + 1, 16, 16);
		btn.state = QStyle::State_Enabled;
		btn.state |= item->checkState() == Qt::Checked ? QStyle::State_On : QStyle::State_Off;
		QStyle *style = QApplication::style();
		style->drawControl(QStyle::CE_CheckBox, &btn, painter);
		//style->drawControl(QStyle::CE_RadioButton, &btn, painter);
	}
}

QSize CoverWidgetItemDelegate::sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const
{
	int size = Settings::instance()->value("CoverFetcher/coverValueSize").toInt();
	QSize s(size, size);
	return s;
}
