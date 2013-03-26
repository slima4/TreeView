#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileSystemModel>
#include <QScrollBar>
#include <QAbst>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QItemModel

    ui->treeView_1->setModel(model);
    ui->treeView_2->setModel(model);
    ui->treeView_1->hideColumn(0);

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






















