#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>
#include <QScrollBar>
#include <QStandardItemModel>
#include <qDebug>

#include "checkboxdelegate.h"
#include "checkboxitem.h"
#include "progressitem.h"
#include "progressdelegate.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _model = new CColorModel(/*0,7,*/this);
    _model->insertColumns(0, 7);

    _model->setHeaderData(0, Qt::Horizontal, QObject::tr("Products"));
    _model->setHeaderData(1, Qt::Horizontal, QObject::tr("Total"));
    _model->setHeaderData(2, Qt::Horizontal, QObject::tr("Northeast"));
    _model->setHeaderData(3, Qt::Horizontal, QObject::tr("Southeast"));
    _model->setHeaderData(4, Qt::Horizontal, QObject::tr("Midwest"));
    _model->setHeaderData(5, Qt::Horizontal, QObject::tr("West"));
    _model->setHeaderData(6, Qt::Horizontal, QObject::tr(""));

    for(int i = 0; i < 100; ++i)
    {
        QList<QStandardItem*> rootItems;
        rootItems << new QStandardItem(QString("Brand Alpha").arg(i));;


        int total = 0;
        for(int j = 0; j < 10; ++j)
        {
            int rand = qrand()%10+1;
            QStandardItem* child1 = new QStandardItem();
            child1->setData(QVariant::fromValue(CProgressItem(rand)), Qt::DisplayRole);
            child1->setData(QString("%1%").arg(rand), Qt::UserRole);
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
        rootItems.last()->setData(QVariant::fromValue(CProgressItem(total)), Qt::DisplayRole);
        rootItems.last()->setData(QString("%1%").arg(total), Qt::UserRole);
        rootItems << new QStandardItem(QString("%1%").arg(total));

        rootItems << new QStandardItem(QString("%1%").arg(total));
        rootItems << new QStandardItem(QString("%1%").arg(total));
        rootItems << new QStandardItem(QString("%1%").arg(total));
        rootItems << new QStandardItem();

        _model->appendRow(rootItems);
    }
    ui->treeView_1->setModel(_model);
    ui->treeView_1->setItemDelegate(new CCheckBoxDelegate);
    ui->treeView_2->setModel(_model);
    ui->treeView_2->setItemDelegate(new CProgressDelegate);
    for(int i = 0; i < ui->treeView_1->model()->columnCount(); ++i)
        ui->treeView_1->hideColumn(i);
    ui->treeView_1->showColumn(6);
    ui->treeView_2->hideColumn(6);

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
        if(checked)
        {
            _model->setData(parentModel.child(model.row(), col), 0, CellValue);
            if(col == 1)
            {
                _model->setData(parentModel.child(model.row(), col),QString("%1%").arg(0), Qt::UserRole);
            }
            else
            {
                _model->setData(parentModel.child(model.row(), col), QString("%1%").arg(0));
            }
        }
        else
        {
            qint32 rand = (qrand()%10 + 1);
            if(col == 1)
            {
                _model->setData(parentModel.child(model.row(), col),QString("%1%").arg(rand), Qt::UserRole);
            }
            else
            {
                _model->setData(parentModel.child(model.row(), col), QString("%1%").arg(rand));
            }
            _model->setData(parentModel.child(model.row(), col), rand, CellValue);
        }
        for(int row = 0; row < 10; ++row)
        {
            total += parentModel.child(row, col).data(CellValue).toInt();
        }
        if(col == 1)
        {
            _model->setData(_model->index(parentModel.row(), col), QString("%1%").arg(total), Qt::UserRole);
        }
        else
        {
            _model->setData(_model->index(parentModel.row(), col), QString("%1%").arg(total));
        }
        qDebug() << "total = " << total;
    }
}






















