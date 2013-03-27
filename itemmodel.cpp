//#include "itemmodel.h"
//#include "item.h"

//CItemModel::CItemModel(QObject *parent) :
//    QAbstractItemModel(parent)
//{
//    _rootItem = new CItem();
//}

//CItemModel::~CItemModel()
//{
//    delete _rootItem;
//}

//QVariant CItemModel::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//    if (role != Qt::DisplayRole)
//        return QVariant();

//    switch (index.column()) {
//        case 0:
//            return "X1";
//        case 1:
//            return "X2";
//        case 2:
//            return "X3";
//        case 3:
//            return "X4";
//        case 4:
//            return "X5";
//        default:
//            return QVariant();
//    }
//}

//QVariant CItemModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
//        switch (section) {
//            case 0:
//                return tr("Name");
//            case 1:
//                return tr("Attributes");
//            case 2:
//                return tr("Value");
//            case 3:
//                return tr("Value2");
//            case 4:
//                return tr("Value3");
//            default:
//                return QVariant();
//        }
//    }

//    return QVariant();
//}

//QModelIndex CItemModel::index(int row, int column, const QModelIndex &parent) const
//{
//    if (!hasIndex(row, column, parent))
//        return QModelIndex();

//    CItem *parentItem;

//    if (!parent.isValid())
//        parentItem = _rootItem;
//    else
//        parentItem = static_cast<CItem*>(parent.internalPointer());

//    CItem *childItem = parentItem->child(row);
//    if (childItem)
//        return createIndex(row, column, childItem);
//    else
//        return QModelIndex();
//}

//QModelIndex CItemModel::parent(const QModelIndex &child) const
//{
//    if (!child.isValid())
//        return QModelIndex();

//    CItem *childItem = static_cast<CItem*>(child.internalPointer());
//    CItem *parentItem = childItem->parent();

//    if (!parentItem || parentItem == rootItem)
//        return QModelIndex();
//}

//int CItemModel::rowCount(const QModelIndex &parent) const
//{
//    if (parent.column() > 0)
//        return 0;

//    CItem *parentItem;

//    if (!parent.isValid())
//        parentItem = rootItem;
//    else
//        parentItem = static_cast<CItem*>(parent.internalPointer());

//    return parentItem->node().childNodes().count();
//}

//int CItemModel::columnCount(const QModelIndex &parent) const
//{
//    return 5;
//}

//Qt::ItemFlags CItemModel::flags(const QModelIndex &index) const
//{
//    if (!index.isValid())
//        return 0;

//    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
//}
