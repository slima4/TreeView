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
    for(int i = OFFSET_COLUMN_BEGIT; i < ROWS_COUNT + OFFSET_COLUMN_BEGIT; ++i)
    {
        // add ROOT
        QList<QStandardItem*> rootItems;
        if(currentName.compare(groupMap[lines.at(i).at(GROUP_COLUMN)], Qt::CaseSensitive) != 0)
        {
            currentName = groupMap[lines.at(i).at(GROUP_COLUMN)];
            rootItems << new QStandardItem(currentName);
        }
        QMap<int,double> totalMap;
        // add CHILD
        while (i < lines.count() && currentName.compare(groupMap[lines.at(i).at(GROUP_COLUMN)], Qt::CaseSensitive) == 0)
        {
            QList<QStandardItem*> items;
            QStandardItem* item;

            items << new QStandardItem(lines.at(i).at(GROUP_COLUMN + 1));

            item = new QStandardItem();
            double value = lines.at(i).at(GROUP_COLUMN + 2).toDouble() * 100;
            totalMap[0] += value;
            item->setData(QVariant::fromValue(CProgressItem(value, QString("%1%").arg(QString::number(value, 'f', 2)))), Qt::DisplayRole);
            item->setData(value, CellValue);
            items << item;


            for(int k = 3; k < 7; ++k)
            {
                value = lines.at(i).at(GROUP_COLUMN + k).toDouble() * 100;
                totalMap[k-2] += value;
                item = new QStandardItem(QString("%1%").arg(QString::number(value, 'f', 2)));
                item->setData(value, CellValue);
                items << item;
            }
            for(int k = 7; k < 15; ++k)
            {
                value = lines.at(i).at(GROUP_COLUMN + k).toDouble()/* * 100*/;
                item = new QStandardItem(QString("%1%").arg(QString::number(value, 'f', 2)));
                item->setData(value, CellValue);
                items << item;
            }

            item = new QStandardItem();
            item->setData(QVariant::fromValue(CCheckBoxItem()), Qt::DisplayRole);
            item->setData(true, Qt::UserRole);
            items << item;

            rootItems.first()->appendRow(items);
            ++i;
        };
        --i;
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
    ui->treeView_1->showColumn(_model->columnCount()-1);
    ui->treeView_2->hideColumn(_model->columnCount()-1);
    ui->treeView_2->resizeColumnToContents(0);

    connect(ui->treeView_1, SIGNAL(clicked(QModelIndex)), SLOT(onCheckBoxClicked(QModelIndex)));
    connect(ui->treeView_2->verticalScrollBar(), SIGNAL(valueChanged(int)),
            ui->treeView_1->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->treeView_1->verticalScrollBar(), SIGNAL(valueChanged(int)),
            ui->treeView_2->verticalScrollBar(), SLOT(setValue2(int)));

    connect(ui->treeView_2, SIGNAL(expanded(QModelIndex)), SLOT(onExpanded(QModelIndex)));
    connect(ui->treeView_2, SIGNAL(collapsed(QModelIndex)), SLOT(onCollapsed(QModelIndex)));


    ui->treeView_2->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->treeView_2->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->treeView_1->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
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






















