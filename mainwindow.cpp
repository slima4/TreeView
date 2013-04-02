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

    _model = new CColorModel(/*0,8,*/this);
    _model->insertColumns(0, 8);

    _model->setHeaderData(0, Qt::Horizontal, QObject::tr("Products"));
    _model->setHeaderData(1, Qt::Horizontal, QObject::tr("Total"));
    _model->setHeaderData(2, Qt::Horizontal, QObject::tr("Northeast"));
    _model->setHeaderData(3, Qt::Horizontal, QObject::tr("Southeast"));
    _model->setHeaderData(4, Qt::Horizontal, QObject::tr("Midwest"));
    _model->setHeaderData(5, Qt::Horizontal, QObject::tr("West"));
    _model->setHeaderData(6, Qt::Horizontal, QObject::tr(""));
    _model->setHeaderData(7, Qt::Horizontal, QObject::tr("Available"));

    for(int i = 0; i < 100; ++i)
    {
        QList<QStandardItem*> rootItems;
        rootItems << new QStandardItem(QString("Brand Alpha").arg(i));;


        int total = 0;
        for(int j = 0; j < 10; ++j)
        {
            QStandardItem* child1 = new QStandardItem();
            child1->setData(QVariant::fromValue(CProgressItem()), Qt::DisplayRole);

            QStandardItem* child2 = new QStandardItem();
            child2->setData(QVariant::fromValue(CCheckBoxItem()), Qt::DisplayRole);
            child2->setData(false, Qt::UserRole);

            rootItems.first()->appendRow(QList<QStandardItem*>() <<
                              new QStandardItem(QString("Product_%1").arg(j)) <<
                              new QStandardItem(QString("%1%").arg(j)) <<
                              new QStandardItem(QString("%1%").arg(j)) <<
                              new QStandardItem(QString("%1%").arg(j)) <<
                              new QStandardItem(QString("%1%").arg(j)) <<
                              new QStandardItem(QString("%1%").arg(j)) <<
                              child1 <<
                              child2);
            total += j;
        }

        rootItems << new QStandardItem(QString("%1% Total").arg(total));

        rootItems << new QStandardItem(QString("%1% Total").arg(total));
        rootItems << new QStandardItem(QString("%1% Total").arg(total));
        rootItems << new QStandardItem(QString("%1% Total").arg(total));
        rootItems << new QStandardItem(QString("%1% Total").arg(total));
        rootItems << new QStandardItem();
        rootItems.last()->setData(QVariant::fromValue(CProgressItem()), Qt::DisplayRole);
        rootItems << new QStandardItem();

        _model->appendRow(rootItems);
    }
    ui->treeView_1->setModel(_model);
    ui->treeView_1->setItemDelegate(new CCheckBoxDelegate);
    ui->treeView_2->setModel(_model);
    ui->treeView_2->setItemDelegate(new CProgressDelegate);
    for(int i = 0; i < ui->treeView_1->model()->columnCount(); ++i)
        ui->treeView_1->hideColumn(i);
    ui->treeView_1->showColumn(7);
    ui->treeView_2->hideColumn(7);

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

    for(int col = 0; col < 8; ++col)
    {
        for(int row = 1; row <= 5; ++row)
        {
            qDebug() << parentModel.child(row, col).data().toString();
        }
    }

//    int c = root.row();
    for(int i = 0; i < 8; ++i)
    {

    }
//    QList<QStandardItem*> items = _model->takeRow(model.row());
////    QStandardItem *item = items[model.row()-1];
//    for(int i = 0; i < 8; ++i)
//    {
//        _model->setData(_model->indexFromItem(items[i]), !checked?QBrush(Qt::blue):QBrush(), Qt::BackgroundRole);
//    }
}






















