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
            int rand = qrand()%10;
            QStandardItem* child1 = new QStandardItem();
            child1->setData(QVariant::fromValue(CProgressItem(rand)), Qt::DisplayRole);
            child1->setData(QString("%1%").arg(rand), Qt::UserRole);
//            child1->setData();

            QStandardItem* child2 = new QStandardItem();
            child2->setData(QVariant::fromValue(CCheckBoxItem()), Qt::DisplayRole);
            child2->setData(true, Qt::UserRole);

            rootItems.first()->appendRow(QList<QStandardItem*>() <<
                              new QStandardItem(QString("Product_%1").arg(rand)) <<
                              child1 <<
                              new QStandardItem(QString("%1%").arg(rand)) <<
                              new QStandardItem(QString("%1%").arg(rand)) <<
                              new QStandardItem(QString("%1%").arg(rand)) <<
                              new QStandardItem(QString("%1%").arg(rand)) <<
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
        for(int row = 0; row < 10; ++row)
        {
            qDebug() << parentModel.child(row, col).data().toString();
        }
        qDebug() << "<<<<<<<<<<<<<<";
    }

//    int c = root.row();
    for(int i = 0; i < 7; ++i)
    {

    }
//    QList<QStandardItem*> items = _model->takeRow(model.row());
////    QStandardItem *item = items[model.row()-1];
//    for(int i = 0; i < 8; ++i)
//    {
//        _model->setData(_model->indexFromItem(items[i]), !checked?QBrush(Qt::blue):QBrush(), Qt::BackgroundRole);
//    }
}






















