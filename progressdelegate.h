#ifndef PROGRESSDELEGATE_H
#define PROGRESSDELEGATE_H

#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>

class CProgressDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CProgressDelegate(QObject *parent = 0);

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
    QPolygonF starPolygon;
};

#endif // PROGRESSDELEGATE_H
