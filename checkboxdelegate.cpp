#include "checkboxdelegate.h"
#include "checkboxitem.h"

#include <QApplication>
#include <qmath.h>

const int PaintingScaleFactor = 20;
CCheckBoxDelegate::CCheckBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

void CCheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
           const QModelIndex &index) const {
    if (index.data().canConvert<CCheckBoxItem>()) {
        QRect buttonRect( option.rect);
        buttonRect.setHeight( 30);
        QStyleOptionButton button;
        button.rect = buttonRect;
        button.state |= QStyle::State_Enabled;
        button.state |= QStyle::State_On;

        QApplication::style()->drawControl(QStyle::CE_CheckBox, &button, painter);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize CCheckBoxDelegate::sizeHint(const QStyleOptionViewItem &option,
               const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

bool CCheckBoxDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                 const QStyleOptionViewItem &option,
                 const QModelIndex &index)
{
    return true;
}
