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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _model = new CColorModel(this);
    _model->setColumnCount(EColumnCount);
    for(int i = 1; i <= 100; ++i)
    {
        QList<QStandardItem*> rootItems;
        rootItems << new QStandardItem(QString("Brand %1").arg(i));

        int total = 0;
        for(int j = 1; j <= 10; ++j)
        {
            int rand = qrand()%10+1;

            QStandardItem* child1 = new QStandardItem();
            child1->setData(QVariant::fromValue(CProgressItem(rand, QString("%1%").arg(rand))), Qt::DisplayRole);
            child1->setData(rand, CELL_VALUE);

            QStandardItem* child2 = new QStandardItem();
            child2->setData(QVariant::fromValue(CCheckBoxItem()), Qt::DisplayRole);
            child2->setData(true, Qt::UserRole);


            QStandardItem *item1 = new QStandardItem(QString("Product_%1").arg(j));
            item1->setData(rand, CELL_VALUE);
            QStandardItem *item2 = new QStandardItem(QString("%1%").arg(rand));
            item2->setData(rand, CELL_VALUE);
            QStandardItem *item3 = new QStandardItem(QString("%1%").arg(rand));
            item3->setData(rand, CELL_VALUE);
            QStandardItem *item4 = new QStandardItem(QString("%1%").arg(rand));
            item4->setData(rand, CELL_VALUE);
            QStandardItem *item5 = new QStandardItem(QString("%1%").arg(rand));
            item5->setData(rand, CELL_VALUE);
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

    ui->treeViewCheckBox->setModel(_model);
    ui->treeViewCheckBox->setItemDelegateForColumn(EColumnCheckBox, new CCheckBoxDelegate);
    ui->treeViewMain->setModel(_model);
    ui->treeViewMain->setItemDelegateForColumn(EColumnTatal, new CProgressDelegate);

    // hide all colums except checkbox column
    for(int i = 0; i < EColumnCheckBox; ++i)
        ui->treeViewCheckBox->hideColumn(i);

    // hide checkbox for main treeview
    ui->treeViewMain->hideColumn(EColumnCheckBox);
    ui->treeViewMain->resizeColumnToContents(0);

    connect(ui->treeViewMain->verticalScrollBar(), SIGNAL(valueChanged(int)),
            ui->treeViewCheckBox->verticalScrollBar(), SLOT(setValue(int)));
    connect(ui->treeViewCheckBox->verticalScrollBar(), SIGNAL(valueChanged(int)),
            ui->treeViewMain->verticalScrollBar(), SLOT(setValue2(int)));

    connect(ui->treeViewMain, SIGNAL(expanded(QModelIndex)), SLOT(onExpanded(QModelIndex)));
    connect(ui->treeViewMain, SIGNAL(collapsed(QModelIndex)), SLOT(onCollapsed(QModelIndex)));


    ui->treeViewMain->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->treeViewMain->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->treeViewCheckBox->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

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
    ui->treeViewCheckBox->verticalScrollBar()->setValue(value);
}

void MainWindow::setValue2(int value)
{
    ui->treeViewMain->verticalScrollBar()->setValue(value);
}

void MainWindow::onExpanded(const QModelIndex &model)
{
    ui->treeViewCheckBox->expand(model);
}

void MainWindow::onCollapsed(const QModelIndex &model)
{
    ui->treeViewCheckBox->collapse(model);
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
    ui->treeViewCheckBox->model()->setData(model, !checked, Qt::UserRole);

    QModelIndex parentModel = model.parent();

    for(int col = 1; col <= 5; ++col)
    {
        qint32 total = 0;
        qint32 rand = 0;
        if(!checked)
            rand = (qrand()%10 + 1);

        _model->setData(parentModel.child(model.row(), col), rand, CELL_VALUE);
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
            total += parentModel.child(row, col).data(CELL_VALUE).toInt();
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






















