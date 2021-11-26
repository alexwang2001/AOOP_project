#ifndef DATABASE_H
#define DATABASE_H


#include <QSqlDatabase>
#include <QSqlResult>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

typedef unsigned short int  USI;

class Database
{
private:
    QSqlDatabase database;
    QSqlQuery *query;
    QString ipAddress;
    USI port;

public:
    Database();
    ~Database();
    bool initializeDB(QString username, QString password, USI port);


};

#endif // DATABASE_H
