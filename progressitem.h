#ifndef PROGRESSITEM_H
#define PROGRESSITEM_H

#include <QMetaType>
#include <QString>

class CProgressItem
{
public:
    CProgressItem() :
        _value(0),
        _textValue(QString())
    {}

    CProgressItem(int value, const QString &text) :
        _value(value),
        _textValue(text)
    {}

    int value() const { return _value; }

    QString text() const {return _textValue; }

private:
    int _value;
    QString _textValue;
};

Q_DECLARE_METATYPE(CProgressItem)

#endif // PROGRESSITEM_H
