#include<QtGui>
#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H
class InventoryItem
{
    friend class LoginManager;
public :
    InventoryItem(QString, QString, int, int);
private :
    QString _ID;
    QString _name;
    QString _room;
    int _type;
    int _price;
};

#endif // INVENTORYITEM_H
