#include "databasesystem.h"

DatabaseSystem::DatabaseSystem(){

}

bool DatabaseSystem::initializeDB(QString hostname, QString username, QString password, USI port){

    // set database
    data_base = QSqlDatabase::addDatabase("QMYSQL");
    data_base.setDatabaseName("trainsystem");
    data_base.setHostName(hostname);
    data_base.setUserName(username);
    data_base.setPassword(password);
    data_base.setPort(port);

    if(!data_base.open()){
        data_base.removeDatabase("QMYSQL");
        return false;
    }
    qDebug() << "Database Error: " << data_base.lastError();
    // set query
    dquery = new QSqlQuery;
    *dquery = QSqlQuery(data_base);

    if(dquery == NULL)
        return false;

    return true;
}

bool DatabaseSystem::initializeDB(){

    // set database
    data_base = QSqlDatabase::addDatabase("QMYSQL");
    data_base.setDatabaseName("trainsystem");
    data_base.setHostName("localhost");
    data_base.setUserName("root");
    data_base.setPassword("qzp,wxom");
    data_base.setPort(3306);

    if(!data_base.open())
        return false;
    qDebug() << "Database Error: " << data_base.lastError();

    // set query
    dquery = new QSqlQuery;
    *dquery = QSqlQuery(data_base);

    if(dquery == NULL)
        return false;

    return true;
}

DatabaseSystem::~DatabaseSystem(){
    data_base.close();
    delete  dquery;
}
