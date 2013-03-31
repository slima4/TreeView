#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>
#include <QScrollBar>
#include <QStandardItemModel>

#include "checkboxdelegate.h"
#include "checkboxitem.h"
#include "progressitem.h"
#include "progressdelegate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel(0,8,this);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Products"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Total"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Northeast"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Southeast"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Midwest"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("West"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr(""));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Available"));

    for(int i = 0; i < 100; ++i)
    {
        QStandardItem *parent = new QStandardItem(QString("test_%1").arg(i));
        parent->setData();
        model->insertRow(0);
        model->appendRow(parent);
        model->setData(model->index(0, 0), QString("%1%").arg(i));
        model->setData(model->index(0, 1), QString("%1%").arg(i));
        model->setData(model->index(0, 2), QString("%1%").arg(i));
        model->setData(model->index(0, 3), QString("%1%").arg(i));
        model->setData(model->index(0, 4), QString("%1%").arg(i));
        model->setData(model->index(0, 5), QString("%1%").arg(i));
        model->setData(model->index(0, 6), QVariant::fromValue(CProgressItem()));
        model->setData(model->index(0, 7), QVariant::fromValue(CCheckBoxItem()));
    }

    ui->treeView_1->setModel(model);
    ui->treeView_1->setItemDelegate(new CCheckBoxDelegate);
    ui->treeView_2->setModel(model);
    ui->treeView_2->setItemDelegate(new CProgressDelegate);
    for(int i = 0; i < ui->treeView_1->model()->columnCount(); ++i)
        ui->treeView_1->hideColumn(i);
    ui->treeView_1->showColumn(7);
    ui->treeView_2->hideColumn(7);

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






















