#include "databasemanager.h"
#include <iostream>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>


QSqlDatabase DataBaseManager::db=  QSqlDatabase::addDatabase("QMYSQL");

void DataBaseManager::createInstance()
{
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("StreamUsers");
    //test connection
    if(db.open())
        qDebug()<<"database connected ";
    else{
        qDebug()<<"database failed to connect ";
        qDebug() << db.lastError();
    }
}

QSqlDatabase* DataBaseManager::getDbInstance()
{
    return &db;
}
