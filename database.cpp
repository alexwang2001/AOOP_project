#include "database.h"

Database::Database(){

}

bool Database::initializeDB(QString username, QString password, USI port){

    // set database
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setDatabaseName("trainsystem");
    database.setUserName(username);
    database.setPassword(password);
    database.setPort(port);

    if(!database.open())
        return false;

    // set query
    query = new QSqlQuery;
    *query = QSqlQuery(database);

    return true;
}

Database::~Database(){
    delete  query;
}
