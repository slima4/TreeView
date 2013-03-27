#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>

class CCheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CCheckBoxDelegate(QObject *parent = 0);

    QPoint closeIconPos(const QStyleOptionViewItem &option) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;

    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index);
signals:
    void closeIndexClicked(const QModelIndex &);

private:
    bool _isChecked;
    QPolygonF starPolygon;
    QPixmap m_closeIcon;
    static const int margin = 2; // pixels to keep arount the icon
};

#endif // CHECKBOXDELEGATE_H
