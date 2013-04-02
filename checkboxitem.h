#ifndef CHECKBOXITEM_H
#define CHECKBOXITEM_H

#include <QMetaType>

class CCheckBoxItem
{
public:
    CCheckBoxItem();

    bool isChecked();
    void checked(bool);

private:
    bool _isChecked;
};

Q_DECLARE_METATYPE(CCheckBoxItem)

#endif // CHECKBOXITEM_H
