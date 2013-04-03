#ifndef PROGRESSITEM_H
#define PROGRESSITEM_H

#include <QMetaType>

class CProgressItem
{
public:
    CProgressItem();
    CProgressItem(int value, const QString &text) :
        _value(value),
        _text(text)
    {}

    int value() { return _value; }

    QString text() {return _text; }

private:
    int _value;
    QString _text;
};

Q_DECLARE_METATYPE(CProgressItem)

#endif // PROGRESSITEM_H
