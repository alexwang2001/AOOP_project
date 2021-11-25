#include "people.h"

People::People()
{

}

People::~People(){

}

QString People::getAccount(){
    return account;
}

QString People::getPassword(){
    return password;
}

void People::setAccount(QString acc){
    account=acc;
}

void People::setNewPassword(QString new_pass){
    password=new_pass;
}

int People::accountVerify(QString acc, QString pass){
    if(acc==account && pass==password) return BOTHRIGHT;
    else if(acc!=account) return ACCOUNTWRONG;
    else return PASSWORDWRONG;
}

bool Client::buyTickets(vector<Ticket> new_tickets){
    for(Ticket ticket: new_tickets) tickets.push_back(ticket);
    return true;
}

bool Client::modifyTickets(int old_tickets, vector<Ticket> new_tickets){
    tickets.erase(tickets.begin()+old_tickets);
    for(Ticket ticket: new_tickets) tickets.push_back(ticket);
    return true;
}

bool Client::cancelTickets(int old_tickets){
    tickets.erase(tickets.begin()+old_tickets);
    return true;
}

bool Staff::getTickets(vector<Ticket> new_tickets){
    for(Ticket ticket: new_tickets) tickets.push_back(ticket);
    return true;
}

bool Staff::modifyTickets(int old_tickets, vector<Ticket> new_tickets){
    tickets.erase(tickets.begin()+old_tickets);
    for(Ticket ticket: new_tickets) tickets.push_back(ticket);
    return true;
}

bool Staff::cancelTickets(int old_tickets){
    tickets.erase(tickets.begin()+old_tickets);
    return true;
}
