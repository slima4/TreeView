#include "checkboxitem.h"

CCheckBoxItem::CCheckBoxItem() :
    _isChecked(false)
{
}

bool CCheckBoxItem::isChecked()
{
    return _isChecked;
}

void CCheckBoxItem::checked(bool check)
{
    _isChecked = check;
}
