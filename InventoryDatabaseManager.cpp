#include<QtSql>
#include "InventoryDatabaseManager.h"
#define UNSPECIFIED -1

InventoryDatabaseManager::InventoryDatabaseManager()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/harshit/my.sqlite.db");

}

InventoryDatabaseManager* InventoryDatabaseManager::_instance = 0;

InventoryDatabaseManager* InventoryDatabaseManager::Instance()
{
    if(_instance==0)
        _instance = new InventoryDatabaseManager();
    return _instance;
}

/*QList<InventoryItem> InventoryDatabaseManager::findInventoryItems(QString locationID, int type)
{
    if(db.open())
    {
        QList<InventoryItem> list;
        QString queryString;
        if(locationID.length()==0 && type == UNSPECIFIED)
        {
            queryString = "SELECT * FROM Inventory";
        }
        else if(type == UNSPECIFIED)
        {
            queryString = QString("SELECT * FROM Inventory WHERE locationID = ").append(locationID);
        }
        else if(type == UNSPECIFIED)
        {
            queryString = QString("SELECT * FROM Inventory WHERE type = %1").arg(type);
        }
        else
        {
            queryString = QString("SELECT * FROM Inventory WHERE type = %1 AND locationID = ").append(locationID);
        }
        QSqlQuery query(queryString, db);
        query.exec();
        while(query.next())
        {
            list.append(InventoryItem(query.value(0).toString(), query.value(1).toString(), query.value(2).toInt()));
        }
        db.close();
        return list;
       }
}*/


