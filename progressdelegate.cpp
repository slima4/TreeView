#include <qmath.h>

#include "progressdelegate.h"
#include "progress.h"

const int PaintingScaleFactor = 20;

CProgressDelegate::CProgressDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    starPolygon << QPointF(1.0, 0.5);
    for (int i = 1; i < 5; ++i)
        starPolygon << QPointF(0.5 + 0.5 * cos(0.8 * i * 3.14),
                               0.5 + 0.5 * sin(0.8 * i * 3.14));
}

QPoint CProgressDelegate::closeIconPos(const QStyleOptionViewItem &option) const {
    return QPoint(option.rect.right() - 2,
                  option.rect.center().y());
}

void CProgressDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
           const QModelIndex &index) const {
    if (index.data().canConvert<CProgress>()) {
        if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());

        painter->save();

        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setPen(Qt::NoPen);

        painter->setBrush(option.palette.foreground());

        int yOffset = (option.rect.height() - PaintingScaleFactor) / 2;
        painter->translate(option.rect.x(), option.rect.y() + yOffset);
        painter->scale(PaintingScaleFactor, PaintingScaleFactor);
        painter->drawPolygon(starPolygon, Qt::WindingFill);
        //painter->drawRect(10,10,10,10);
        painter->translate(1.0, 0.0);

        painter->restore();
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
    // Emit a signal when the icon is clicked
    if(!index.parent().isValid() &&
            event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

//        QRect closeButtonRect = m_closeIcon.rect()
//                .translated(closeIconPos(option));

//        if(closeButtonRect.contains(mouseEvent->pos()))
//        {
//            emit closeIndexClicked(index);
//        }
        return true;
    }
    return false;
}
