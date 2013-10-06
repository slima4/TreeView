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

    enum EColumn {
        EColumnBrand = 0,
        EColumnTatal = 1,
        EColumnNortheast = 2,
        EColumnSoutheast = 3,
        EColumnMidwest = 4,
        EColumnWest = 5,
        EColumnCheckBox = 6,

        EColumnCount
    };
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static const int CELL_VALUE = Qt::UserRole + 100;

public slots:
    void setValue(int);
    void setValue2(int);
    void onExpanded(const QModelIndex &);
    void onCollapsed(const QModelIndex &);
    void onCheckBoxClicked(const QModelIndex &);

    void onRbGroceryToggled(bool);
    void onRbMassRetailerToggled(bool);
    void onRbClubStoreToggled(bool);

    void onRbConceptAToggled(bool);
    void onRbConceptBToggled(bool);

    void onRb12ozToggled(bool);
    void onRb16ozToggled(bool);
    void onRb2x16ozToggled(bool);
    
private:
    Ui::MainWindow *ui;
    CColorModel *_model;
};

#endif // MAINWINDOW_H
