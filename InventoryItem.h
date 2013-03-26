#include<QtGui>
#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H
class InventoryItem
{
public :
    InventoryItem(QString, QString, int);
private :
    QString _ID;
    QString _locationID;
    int _type;
};

#endif // INVENTORYITEM_H
