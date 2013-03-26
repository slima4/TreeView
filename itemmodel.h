#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

class CItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    CItemModel(QObject *parent = 0);
    ~CItemModel();

    QVariant data(const QModelIndex &index, int role) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;

    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

private:
    CItemModel *_rootItem;
};

#endif // ITEMMODEL_H
