#ifndef TICKET_H
#define TICKET_H

#include <string>
#include <QDate>
#include <QTime>
#include <QString>
#include <QDebug>

using namespace std;

class Ticket {
private:
    unsigned short int train_number;
    unsigned short int ticket_number;
    QDate train_date;
    QTime train_time;
    QString passenger_departure_station;
    QString passenger_destination_station;
    QString seat;
    unsigned short int carrageNO;
    unsigned int price;

public:
    Ticket();
    ~Ticket();

    Ticket& setTrainNumber(unsigned short int NO);

    Ticket& setTrainTime(QTime time);
    Ticket& setTrainTime(int hour, int minute, int second);

    Ticket& setTrainDate(QDate date);
    Ticket& setTrainDate(int year, int month, int day);

    Ticket& setDepart(QString depart);
    Ticket& setDepart(string depart);

    Ticket& setDestination(QString destination);
    Ticket& setDestination(string destination);

    Ticket& setSeat(QString seatNO);
    Ticket& setSeat(string seatNO);

    Ticket& setCarrageNO(unsigned short int NO);

    Ticket& setPrice(unsigned int cost);

    const unsigned short int& trainNumber();
    const QDate& trainDate();
    const QTime& trainTime();
    const QString& departureStation();
    const QString& destinationStation();
    const QString& seatNo();
    const unsigned short int& carrageNo();
    const unsigned int& Price();

    QString TicketNumber();
    static unsigned short int count;
};



#endif
