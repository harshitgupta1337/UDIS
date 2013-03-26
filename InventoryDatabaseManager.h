#ifndef INVENTORYDATABASEMANAGER_H
#define INVENTORYDATABASEMANAGER_H
#include<QtSql>
#include "InventoryItem.h"
#define UNSPECIFIED -1
class InventoryDatabaseManager
{
    public :
        static InventoryDatabaseManager* Instance();
    protected:
        InventoryDatabaseManager();
    private :
        static InventoryDatabaseManager* _instance;
        QSqlDatabase db;
        QList<InventoryItem> findInventoryItems(QString locationID = "", int type = UNSPECIFIED);
};
#endif // INVENTORYDATABASEMANAGER_H
