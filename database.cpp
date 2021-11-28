#include "database.h"

Database::Database(){

}

bool Database::initializeDB(QString username, QString password, USI port){

    // set database
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setDatabaseName("trainsystem");
    database.setHostName("127.0.0.1");
    database.setUserName(username);
    database.setPassword(password);
    database.setPort(port);

    if(!database.open())
        return false;

    // set query
    query = new QSqlQuery;
    *query = QSqlQuery(database);

    if(query == NULL)
        return false;

    return true;
}

Database::~Database(){
    delete  query;
}
