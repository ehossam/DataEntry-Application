#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <memory>

using namespace std;

class DataBaseManager
{
    static QSqlDatabase db;
public:
    static QSqlDatabase * getDbInstance();
    static void createInstance();
};

#endif // DATABASEMANAGER_H
