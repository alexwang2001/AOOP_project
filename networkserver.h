#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

#include <vector>
#include <string>
#include <QSqlDatabase>
#include <QSqlResult>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "ticket.h"
#include "people.h"

using namespace std;

class NetworkServer {
private:
    vector<Client> clientlist;
    vector<Staff> stafflist;
    vector<Manager> managerlist;
    string connectToIP;
    unsigned short connectToPort;

public:

    NetworkServer();
    ~NetworkServer();

    void newTickets(vector<Ticket> tickets);
    vector<Client>& searchTickets(const vector<Ticket>& tickets);
    // modify tickets
    // cancel tickets


    enum newAccountError{NoError, NameExist};
    int newManager(Manager manager);
    int newClient(Client client);
    int newStaff(Staff staff);
    bool findClinet(QString account, Client&);

    QSqlDatabase database;
    QSqlQuery *query;

};





#endif
