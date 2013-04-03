#ifndef PROGRESSITEM_H
#define PROGRESSITEM_H

#include <QMetaType>

class CProgressItem
{
public:
    CProgressItem();
    CProgressItem(int value) :
        _value(value)
    {}

    int value() { return _value; }

private:
    int _value;
};

Q_DECLARE_METATYPE(CProgressItem)

#endif // PROGRESSITEM_H
