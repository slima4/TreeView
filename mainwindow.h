#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setValue(int);
    void onExpanded(const QModelIndex &);
    void onCollapsed(const QModelIndex &);
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
