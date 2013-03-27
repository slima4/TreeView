#include "checkboxdelegate.h"
#include <QApplication>

#include "starrating.h"
#include <qmath.h>
const int PaintingScaleFactor = 20;
CCheckBoxDelegate::CCheckBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
//    m_closeIcon;
//    if(m_closeIcon.isNull())
//    {
        m_closeIcon = qApp->style()
            ->standardPixmap(QStyle::SP_DialogCloseButton);
//    }

    _isChecked = false;
    starPolygon << QPointF(1.0, 0.5);
    for (int i = 1; i < 5; ++i)
        starPolygon << QPointF(0.5 + 0.5 * cos(0.8 * i * 3.14),
                               0.5 + 0.5 * sin(0.8 * i * 3.14));
}

QPoint CCheckBoxDelegate::closeIconPos(const QStyleOptionViewItem &option) const {
    return QPoint(option.rect.right() - m_closeIcon.width() - margin,
                  option.rect.center().y() - m_closeIcon.height()/2);
}

void CCheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
           const QModelIndex &index) const {
//    QStyledItemDelegate::paint(painter, option, index);
//    // Only display the close icon for top level items...
//    if(!index.parent().isValid()
//            // ...and when the mouse is hovering the item
//            // (mouseTracking must be enabled on the view)
//            && (option.state & QStyle::State_MouseOver))
//    {
//        painter->drawPixmap(closeIconPos(option), m_closeIcon);
//    }
    if (index.data().canConvert<StarRating>()) {
        if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());

        painter->save();

        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->setPen(Qt::NoPen);

        if(_isChecked)
            painter->setBrush(option.palette.highlight());
        else
            painter->setBrush(option.palette.foreground());

        int yOffset = (option.rect.height() - PaintingScaleFactor) / 2;
        painter->translate(option.rect.x(), option.rect.y() + yOffset);
        painter->scale(PaintingScaleFactor, PaintingScaleFactor);
        painter->drawPolygon(starPolygon, Qt::WindingFill);
        painter->translate(1.0, 0.0);

        painter->restore();
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

QSize CCheckBoxDelegate::sizeHint(const QStyleOptionViewItem &option,
               const QModelIndex &index) const
{
    QSize size = QStyledItemDelegate::sizeHint(option, index);

    // Make some room for the close icon
    if(!index.parent().isValid()) {
        size.rwidth() += m_closeIcon.width() + margin * 2;
        size.setHeight(qMax(size.height(),
                            m_closeIcon.height() + margin * 2));
    }
    return size;
}

bool CCheckBoxDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
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
        _isChecked = !_isChecked;
        return true;
    }
    return false;
}
