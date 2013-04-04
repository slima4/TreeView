#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>
#include <QScrollBar>
#include <QStandardItemModel>
#include <qDebug>
#include <QMap>
#include <QPair>

#include "checkboxdelegate.h"
#include "checkboxitem.h"
#include "progressitem.h"
#include "progressdelegate.h"

//#define NEW_MODEL

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
#ifndef NEW_MODEL
    QList<QStringList> lines;
    QFile file("db/SampleProjectDataset_1.csv");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd())
        {
            QString line = file.readLine();
            line.chop(1);
            lines.push_back(QStringList() << line.split(","));
        }
        file.close();
    }

    const qint32 OFFSET_COLUMN_BEGIT = 2;
    const qint32 OFFSET_COLUMN_END = 2;
    const qint32 COLUMNS_COUNT = lines.at(1).size()-OFFSET_COLUMN_END - 1;
    const qint32 ROWS_COUNT = lines.length() - 2;
    const qint32 GROUP_COLUMN = 1;

    const qint32 CHAR_LENG = 3;

    _model = new CColorModel(this);
    _model->insertColumns(0, COLUMNS_COUNT);

    for(int i = OFFSET_COLUMN_BEGIT; i <= COLUMNS_COUNT; ++i)
    {
        _model->setHeaderData(i-OFFSET_COLUMN_BEGIT, Qt::Horizontal, lines.at(1).at(i));
    }
    // last row for checkboxs
    _model->setHeaderData(COLUMNS_COUNT - 1, Qt::Horizontal, "");

    QMap<QString, QString> groupMap;
    { // GET_GROUP
        int group_column = 0;
        bool founded = false;
        for(int col = 0; col < lines.at(1).count(); ++col)
        {
            if(lines.at(1).at(col).compare("Group (Brand)",Qt::CaseInsensitive) == 0)
            {
                founded = true;
                group_column = col;
                break;
            }
        }
        if(founded)
        {
            qint32 OFFSET_DATA_BEGIN = 2;
            for(int row = OFFSET_DATA_BEGIN; row < lines.count(); ++row)
            {
                if(lines.at(row).at(group_column).isEmpty() || lines.at(row).at(group_column+1).isEmpty())
                    break;
                groupMap.insert(lines.at(row).at(group_column), lines.at(row).at(group_column+1));
            }
        }
    }


    QString currentName;
    for(int row = OFFSET_COLUMN_BEGIT; row < ROWS_COUNT + OFFSET_COLUMN_BEGIT; ++row)
    {
        // add ROOT
        QList<QStandardItem*> rootItems;
        if(currentName.compare(groupMap[lines.at(row).at(GROUP_COLUMN)], Qt::CaseSensitive) != 0)
        {
            currentName = groupMap[lines.at(row).at(GROUP_COLUMN)];
            rootItems << new QStandardItem(currentName);
        }
        // add CHILD
        QMap<int,double> totalMap;
        while (row < lines.count() && currentName.compare(groupMap[lines.at(row).at(GROUP_COLUMN)], Qt::CaseSensitive) == 0)
        {
            bool ok;
            double value = 0;
            QString valueStr;
            QStringList line(lines.at(row));
            int totalSumRow = 0;
            QList<QStandardItem*> items;
            QStandardItem* item;

            items << new QStandardItem(line.at(GROUP_COLUMN + 1));

            item = new QStandardItem();
            value = line.at(GROUP_COLUMN + 2).toDouble(&ok) * 100;
            if(ok)
                valueStr = QString("%1%").arg(QString::number(value, 'f', 2));
            else
                valueStr = line.at(GROUP_COLUMN + 2);
            item->setData(QVariant::fromValue(CProgressItem(value, valueStr)), Qt::DisplayRole);
            totalMap[0] += value;
            totalSumRow += value*100;
            item->setData(value, CellValue);
            items << item;

            for(int k = 3; k < 7; ++k) // main columns
            {
                value = line.at(GROUP_COLUMN + k).toDouble(&ok) * 100;
                totalMap[k-2] += value;
                totalSumRow += value*100;
                if(ok)
                    valueStr = QString("%1%").arg(QString::number(value, 'f', 2));
                else
                    valueStr = line.at(GROUP_COLUMN + k);
                item = new QStandardItem(valueStr);
                item->setData(value, CellValue);
                items << item;
            }

            for(int k = 7; k < 15; ++k) // additional columns
            {
                value = line.at(GROUP_COLUMN + k).toDouble();
                item = new QStandardItem(QString("%1%").arg(QString::number(value, 'f', 2)));
                item->setData(value, CellValue);
                items << item;
            }

            item = new QStandardItem();
            item->setData(QVariant::fromValue(CCheckBoxItem()), Qt::DisplayRole);
            item->setData(totalSumRow <= 0?false:true, Qt::UserRole);
            items << item;

            rootItems.first()->appendRow(items);
            ++row;
        };
        --row;
        rootItems << new QStandardItem();
        rootItems.last()->setData(QVariant::fromValue(CProgressItem(totalMap[0], QString("%1%").arg(QString::number(totalMap[0], 'f', 2)))), Qt::DisplayRole);
        rootItems << new QStandardItem(QString("%1%").arg(QString::number(totalMap[1], 'f', 2)));
        rootItems << new QStandardItem(QString("%1%").arg(QString::number(totalMap[2], 'f', 2)));
        rootItems << new QStandardItem(QString("%1%").arg(QString::number(totalMap[3], 'f', 2)));
        rootItems << new QStandardItem(QString("%1%").arg(QString::number(totalMap[4], 'f', 2)));
        rootItems << new QStandardItem();
        _model->appendRow(rootItems);
    }
#else
    _model = new CColorModel(this);
    _model->insertColumns(0, 7);
    for(int i = 0; i < 100; ++i)
    {
        QList<QStandardItem*> rootItems;
        rootItems << new QStandardItem(QString("Brand Alpha").arg(i));

        int total = 0;
        for(int j = 0; j < 10; ++j)
        {
            int rand = qrand()%10+1;
            QStandardItem* child1 = new QStandardItem();
            child1->setData(QVariant::fromValue(CProgressItem(rand, QString("%1%").arg(rand))), Qt::DisplayRole);
            child1->setData(rand, CellValue);

            QStandardItem* child2 = new QStandardItem();
            child2->setData(QVariant::fromValue(CCheckBoxItem()), Qt::DisplayRole);
            child2->setData(true, Qt::UserRole);


            QStandardItem *item1 = new QStandardItem(QString("Product_%1").arg(j));
            item1->setData(rand, CellValue);
            QStandardItem *item2 = new QStandardItem(QString("%1%").arg(rand));
            item2->setData(rand, CellValue);
            QStandardItem *item3 = new QStandardItem(QString("%1%").arg(rand));
            item3->setData(rand, CellValue);
            QStandardItem *item4 = new QStandardItem(QString("%1%").arg(rand));
            item4->setData(rand, CellValue);
            QStandardItem *item5 = new QStandardItem(QString("%1%").arg(rand));
            item5->setData(rand, CellValue);
            rootItems.first()->appendRow(QList<QStandardItem*>() <<
                              item1 <<
                              child1 <<
                              item2 <<
                              item3 <<
                              item4 <<
                              item5 <<
                              child2);
            total += rand;
        }
        rootItems << new QStandardItem();
        rootItems.last()->setData(QVariant::fromValue(CProgressItem(total, QString("%1%").arg(total))), Qt::DisplayRole);
        rootItems << new QStandardItem(QString("%1%").arg(total));
        rootItems << new QStandardItem(QString("%1%").arg(total));
        rootItems << new QStandardItem(QString("%1%").arg(total));
        rootItems << new QStandardItem(QString("%1%").arg(total));
        rootItems << new QStandardItem();

        _model->appendRow(rootItems);
    }
#endif
    ui->treeView_1->setModel(_model);
    ui->treeView_1->setItemDelegate(new CCheckBoxDelegate);
    ui->treeView_2->setModel(_model);
    ui->treeView_2->setItemDelegate(new CProgressDelegate);
    for(int i = 0; i < ui->treeView_1->model()->columnCount(); ++i)
        ui->treeView_1->hideColumn(i);
    for(int i = 6; i < ui->treeView_2->model()->columnCount(); ++i)
        ui->treeView_2->hideColumn(i);
    ui->treeView_1->showColumn(_model->columnCount()-1);
    ui->treeView_2->hideColumn(_model->columnCount()-1);
    ui->treeView_2->resizeColumnToContents(0);
//    int rrr = _model->rowCount();

//    for(int i = 0; i < _model->rowCount(); ++i)
//    {
//        QStandardItem *itemChild = _model->item(i);

//        QMap<int,double> totalMap;
//        double coef = itemChild->child(i, 6)->data(CellValue).toDouble();
//        bool ok;
//        QString valueStr;
//        for(int j = 1; j < 6; ++j)
//        {
//            QStandardItem *item = itemChild->child(i, j);
//            double value = item->data(CellValue).toDouble(&ok) * coef;
//            totalMap[j] += value;
//            if(ok)
//                valueStr = QString("%1%").arg(QString::number(value, 'f', 2));
//            else
//                valueStr = "--";
//            item->setData(valueStr, Qt::DisplayRole);
//            item->setData(value, CellValue);
//        }
//    }

    //connect(ui->treeView_1, SIGNAL(clicked(QModelIndex)), SLOT(onCheckBoxClicked(QModelIndex)));
    connect(ui->treeView_2->verticalScrollBar(), SIGNAL(valueChanged(int)),
            ui->treeView_1->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->treeView_1->verticalScrollBar(), SIGNAL(valueChanged(int)),
            ui->treeView_2->verticalScrollBar(), SLOT(setValue2(int)));

    connect(ui->treeView_2, SIGNAL(expanded(QModelIndex)), SLOT(onExpanded(QModelIndex)));
    connect(ui->treeView_2, SIGNAL(collapsed(QModelIndex)), SLOT(onCollapsed(QModelIndex)));


    ui->treeView_2->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->treeView_2->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->treeView_1->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    connect(ui->rbGrocery, SIGNAL(toggled(bool)), SLOT(onRbGroceryToggled(bool)));
    connect(ui->rbMassRetailer, SIGNAL(toggled(bool)), SLOT(onRbMassRetailerToggled(bool)));
    connect(ui->rbClubStore, SIGNAL(toggled(bool)), SLOT(onRbClubStoreToggled(bool)));

    connect(ui->rbConceptA, SIGNAL(toggled(bool)), SLOT(onRbConceptAToggled(bool)));
    connect(ui->rbConceptB, SIGNAL(toggled(bool)), SLOT(onRbConceptBToggled(bool)));

    connect(ui->rb12oz, SIGNAL(toggled(bool)), SLOT(onRb12ozToggled(bool)));
    connect(ui->rb16oz, SIGNAL(toggled(bool)), SLOT(onRb16ozToggled(bool)));
    connect(ui->rb2x16oz, SIGNAL(toggled(bool)), SLOT(onRb2x16ozToggled(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setValue(int value)
{
    ui->treeView_1->verticalScrollBar()->setValue(value);
}

void MainWindow::setValue2(int value)
{
    ui->treeView_2->verticalScrollBar()->setValue(value);
}

void MainWindow::onExpanded(const QModelIndex &model)
{
    ui->treeView_1->expand(model);
}

void MainWindow::onCollapsed(const QModelIndex &model)
{
    ui->treeView_1->collapse(model);
}

void MainWindow::onRbGroceryToggled(bool toggled)
{

}

void MainWindow::onRbMassRetailerToggled(bool toggled)
{

}

void MainWindow::onRbClubStoreToggled(bool toggled)
{

}

void MainWindow::onRbConceptAToggled(bool toggled)
{

}

void MainWindow::onRbConceptBToggled(bool toggled)
{

}

void MainWindow::onRb12ozToggled(bool toggled)
{

}

void MainWindow::onRb16ozToggled(bool toggled)
{

}

void MainWindow::onRb2x16ozToggled(bool toggled)
{

}

void MainWindow::onCheckBoxClicked(const QModelIndex &model)
{
    bool checked = model.data(Qt::UserRole).toBool();
    ui->treeView_1->model()->setData(model, !checked, Qt::UserRole);

    QModelIndex parentModel = model.parent();

    for(int col = 1; col <= 5; ++col)
    {
        qint32 total = 0;
        qint32 rand = 0;
        if(!checked)
            rand = (qrand()%10 + 1);

        _model->setData(parentModel.child(model.row(), col), rand, CellValue);
        if(col == 1)
        {
            _model->setData(parentModel.child(model.row(), col), QVariant::fromValue(CProgressItem(rand, QString("%1%").arg(rand))), Qt::DisplayRole);
        }
        else
        {
            _model->setData(parentModel.child(model.row(), col), QString("%1%").arg(rand));
        }

        for(int row = 0; row < 10; ++row)
        {
            total += parentModel.child(row, col).data(CellValue).toInt();
        }

        if(col == 1)
        {
            _model->setData(_model->index(parentModel.row(), col), QVariant::fromValue(CProgressItem(total, QString("%1%").arg(total))), Qt::DisplayRole);
        }
        else
        {
            _model->setData(_model->index(parentModel.row(), col), QString("%1%").arg(total));
        }
        qDebug() << "total = " << total;
    }
}






















