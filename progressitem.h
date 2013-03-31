#ifndef PROGRESSITEM_H
#define PROGRESSITEM_H

#include <QMetaType>

class CProgressItem
{
public:
    CProgressItem();

    int value() { return 10; }
};

Q_DECLARE_METATYPE(CProgressItem)

#endif // PROGRESSITEM_H
