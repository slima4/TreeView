#ifndef CCOLORMODEL_H
#define CCOLORMODEL_H

#include <QStandardItemModel>

class CColorModel : public QStandardItemModel
{
public:
    CColorModel(QObject *parent)  : QStandardItemModel(parent)
    {

    }
    // Returns an appropriate value for the requested data.
    // If the view requests an invalid index or if the role is not
    // Qt::DisplayRole, Qt::BackgroundColorRole or QTextColorRole, an invalid variant is
    // returned.
    // Any valid index that corresponds to a string for the index's column and row in
    // the stringlist is returned for the Qt::DisplayRole
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
//        if (!index.isValid())
//            return QVariant();
//        if (role == Qt::BackgroundRole)
//        {
//            if(index.data(Qt::UserRole).toBool() == true)
//                return QColor(Qt::red);
//            return QVariant();
//        }
//        else if (role == Qt::ForegroundRole )
//        {
//            if(index.data(Qt::UserRole).toBool() == true)
//                return QColor(Qt::red);
//            return QVariant();
//        }
        return QStandardItemModel::data(index, role);
    }

private:
    // Each row will consist of a list of strings
    QList<QStringList>stringList;
};
#endif // CCOLORMODEL_H
