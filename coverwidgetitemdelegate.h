#ifndef COVERWIDGETITEMDELEGATE_H
#define COVERWIDGETITEMDELEGATE_H

#include <QListWidget>
#include <QStyledItemDelegate>

/**
 * \brief       The CoverWidgetItemDelegate class displays a checkbox on found covers.
 * \details		When one has started a search for covers, multiple ones can be found, dependending how strings are matching and
 *				remote locations are responding. A checkbox has been added in the top-left cover of every picture waiting to be checked before applying changes.
 * \author      Matthieu Bachelier
 * \copyright   GNU General Public License v3
 */
class CoverWidgetItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT
private:
	QListWidget *_listWidget;

public:
	explicit CoverWidgetItemDelegate(QListWidget *parent);

	/** Redefined to display a checkbox in top-left corner. */
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // COVERWIDGETITEMDELEGATE_H
