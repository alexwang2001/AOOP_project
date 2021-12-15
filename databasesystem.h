#ifndef DATABASESYSTEM_H
#define DATABASESYSTEM_H


#include <QSqlDatabase>
#include <QSqlResult>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

typedef unsigned short int  USI;

class DatabaseSystem
{
private:
    QSqlDatabase data_base;
    QSqlQuery *dquery;

public:
    DatabaseSystem();
    ~DatabaseSystem();

    bool initializeDB(QString hostname, QString username, QString password, USI port);
    bool initializeDB();

    const QSqlDatabase& database(){return data_base;};
    QSqlQuery* query(){return dquery;};


};

#endif // DATABASESYSTEM_H
