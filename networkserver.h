#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlResult>
#include <QSqlQuery>
#include <QSqlError>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include "../ticket.h"
#include "../people.h"
#include "../databasesystem.h"

using namespace std;

class NetworkServer {

    Q_OBJECT

public:
    NetworkServer();
    ~NetworkServer();

    void newTickets(vector<Ticket> tickets);
    vector<Client>& searchTickets(const vector<Ticket>& tickets);
    // modify tickets
    // cancel tickets

    // new account
    enum newAccountError{NoError, NameExist, NoAuthority};
    int newManager(Manager manager, QString key);
    int newStaff(Staff staff, QString key);
    int newClient(Client client);
    bool findClinet(QString account, Client&);

    DatabaseSystem *databasesystem;

private:
    QVector<Client> clientlist;
    QVector<Staff> stafflist;
    QVector<Manager> managerlist;

    QString connectToIP;
    unsigned short connectToPort;

    QTcpServer *server;
    QMap<quint32,QTcpSocket*> sockets;

public slots:
    void slot_newConnection();
    void slot_readyRead();
    void slot_disconnect();

};





#endif
