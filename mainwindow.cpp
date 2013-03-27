#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>
#include <QScrollBar>
#include <QStandardItemModel>

#include "checkboxdelegate.h"
#include "stardelegate.h"
#include "starrating.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel(0,5,this);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Subject"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Sender"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ProgressBar"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("CheckBox"));

    for(int i = 0; i < 100; ++i)
    {
        model->insertRow(0);
        model->setData(model->index(0, 0), QString("Subject_%1").arg(i));
        model->setData(model->index(0, 1), QString("Sender_%1").arg(i));
        model->setData(model->index(0, 2), QString("Datet_%1").arg(i));
        model->setData(model->index(0, 3), QString("ProgressBar_%1").arg(i));
        model->setData(model->index(0, 4), QVariant::fromValue(StarRating(2)));
    }


    ui->treeView_1->setModel(model);
    ui->treeView_1->setItemDelegate(new CCheckBoxDelegate);
    ui->treeView_2->setModel(model);
    for(int i = 0; i < ui->treeView_1->model()->columnCount(); ++i)
        ui->treeView_1->hideColumn(i);
    ui->treeView_1->showColumn(4);
    ui->treeView_2->hideColumn(4);

    connect(ui->treeView_2->verticalScrollBar(), SIGNAL(valueChanged(int)),
            ui->treeView_1->verticalScrollBar(), SLOT(setValue(int)));

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

void MainWindow::onExpanded(const QModelIndex &model)
{
    ui->treeView_1->expand(model);
}

void MainWindow::onCollapsed(const QModelIndex &model)
{
    ui->treeView_1->collapse(model);
}






















