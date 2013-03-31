#include <qmath.h>

#include "progressdelegate.h"
#include "progressitem.h"

#include <QDebug>
#include <QApplication>

const int PaintingScaleFactor = 20;

CProgressDelegate::CProgressDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void CProgressDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
           const QModelIndex &index) const
{
    if (index.data().canConvert<CProgressItem>())
    {
        CProgressItem progress = qvariant_cast<CProgressItem>(index.data());
        QRect buttonRect( option.rect);
        buttonRect.setHeight( 30);
        QStyleOptionProgressBar button;
        button.rect = buttonRect;
        button.state = QStyle::State_Enabled;
        button.maximum = 100;
        button.progress = progress.value();

        QApplication::style()->drawControl(QStyle::CE_ProgressBar, &button, painter);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize CProgressDelegate::sizeHint(const QStyleOptionViewItem &option,
               const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);

    return size;
}

bool CProgressDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                 const QStyleOptionViewItem &option,
                 const QModelIndex &index)
{
    Q_UNUSED(event);
    Q_UNUSED(model);
    Q_UNUSED(option);
    Q_UNUSED(index);

    return true;
}
