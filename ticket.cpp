#include "ticket.h"

unsigned short int Ticket::count=0;

Ticket::Ticket(){
    count++;
    ticket_number=count;
}

Ticket::~Ticket(){
    count--;
// release seat
}

Ticket& Ticket::setTrainNumber(unsigned short int NO){
    train_number = NO;
    return *this;
}

Ticket& Ticket::setTrainTime(QTime time){
    train_time = time;
    return *this;
}

Ticket& Ticket::setTrainTime(int hour, int minute, int second){
    QTime time;
    time.setHMS(hour,minute,second);
    train_time = time;
    return *this;
}

Ticket& Ticket::setTrainDate(QDate date){
    train_date = date;
    return *this;
}

Ticket& Ticket::setTrainDate(int year, int month, int day){
    QDate date;
    date.setDate(year, month, day);
    train_date = date;
    return *this;
}

Ticket& Ticket::setDepart(QString depart){
    passenger_departure_station = depart;
    return *this;
}

Ticket& Ticket::setDepart(string depart){
    passenger_departure_station = QString::fromStdString(depart);
    return *this;
}

Ticket& Ticket::setDestination(QString destination){
    passenger_destination_station = destination;
    return *this;
}

Ticket& Ticket::setDestination(string destination){
    passenger_destination_station = QString::fromStdString(destination);
    return *this;
}

Ticket& Ticket::setSeat(QString seatNO){
    seat = seatNO;
    return *this;
}

Ticket& Ticket::setSeat(string seatNO){
    seat = QString::fromStdString(seatNO);
    return *this;
}

Ticket& Ticket::setCarrageNO(unsigned short int NO){
    carriageNO = NO;
    return *this;
}

Ticket& Ticket::setPrice(unsigned int cost){
    price = cost;
    return *this;
}

const unsigned short int& Ticket::trainNumber(){
    return train_number;
}
const QDate& Ticket::trainDate(){
    return train_date;
}
const QTime& Ticket::trainTime(){
    return train_time;
}
const QString& Ticket::departureStation(){
    return passenger_departure_station;
}
const QString& Ticket::destinationStation(){
    return passenger_destination_station;
}
const QString& Ticket::seatNo(){
    return seat;
}
const unsigned short int& Ticket::carrageNo(){
    return carriageNO;
}
const unsigned int& Ticket::Price(){
    return price;
}

QString Ticket::TicketNumber(){
    QString string, digit;
    digit=QString::number(ticket_number);
    for(int i=0; i<5-digit.length(); i++) string+="0";
    string+=digit;
    return string;
}
