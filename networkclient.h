#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QTcpSocket>
#include "ticket.h"
#include "people.h"

typedef unsigned short int USI;

class NetworkClient
{
public:
    NetworkClient();
    ~NetworkClient();
    enum Code{NoError, NameExist};
    //void newTickets(vector<Ticket> tickets);
    //vector<Client>& searchTickets(const vector<Ticket>& tickets);

    bool connectToServer();
    bool login(QString account, QString password);
    void newManagerRequest(Manager manager, QString key);
    void newStaffRequest(Staff staff, QString key);
    void newClientRequest(Client client);

private:
    QString IP;
    USI port;
    QTcpSocket *socket;
    QString response;
    void requestToServer(QString req);

private slots:
    void slot_readyRead();
    void slot_disconnect();
};

#endif // NETWORKCLIENT_H
