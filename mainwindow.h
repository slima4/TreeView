#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

#include "colormodel.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static const int CellValue = Qt::UserRole + 100;

public slots:
    void setValue(int);
    void setValue2(int);
    void onExpanded(const QModelIndex &);
    void onCollapsed(const QModelIndex &);
    void onCheckBoxClicked(const QModelIndex &);
    
private:
    Ui::MainWindow *ui;
    CColorModel *_model;
};

#endif // MAINWINDOW_H
