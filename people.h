#ifndef PEOPLE_H
#define PEOPLE_H

#include <QString>
#include <QDebug>
#include <QTextStream>
#include "ticket.h"

using namespace std;

class People
{
private:
    QString account;
    QString password;


public:
    People();
    ~People();
    int accountVerify(QString acc, QString pass);
    void setAccount(QString acc);
    void setNewPassword(QString new_pass);
    QString getAccount();
    QString getPassword();
    enum account_verify {BOTHRIGHT, ACCOUNTWRONG, PASSWORDWRONG};
};

class Client: public People{
private:
    unsigned int clientID;
    vector<Ticket> tickets;
    int money;

public:
    bool buyTickets(vector<Ticket> new_tickets);
    bool modifyTickets(int old_tickets, vector<Ticket> new_tickets);
    bool cancelTickets(int old_tickets);

};

class Staff: public People{
private:
    unsigned int staffID;
    vector<Ticket> tickets;

public:
    bool getTickets(vector<Ticket> new_tickets);
    bool modifyTickets(int old_tickets, vector<Ticket> new_tickets);
    bool cancelTickets(int old_tickets);
};

class Manager: public Staff{

};



#endif // PEOPLE_H
