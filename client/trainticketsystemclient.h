#ifndef TRAINTICKETSYSTEMCLIENT_H
#define TRAINTICKETSYSTEMCLIENT_H

#include <QMainWindow>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QLabel>
#include <QDebug>
#include <QVector>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QGraphicsView>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QTcpSocket>
#include "../traingraphicview.h"
#include "../people.h"
#include "../ticket.h"
#include "../trainticketsystem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TrainTicketSystemClient; }
QT_END_NAMESPACE

class TrainTicketSystemClient : public QMainWindow, public TrainTicketSystem
{
    Q_OBJECT

public:
    TrainTicketSystemClient(QWidget *parent = nullptr);
    ~TrainTicketSystemClient();

    void switchPage(int idx);
    void set_login_page();
    void set_create_client_account_page();
    void set_create_staff_account_age();
    void set_station_table();

private:
    Ui::TrainTicketSystemClient *ui;

    QDateTime *datetime;
    QTimer *timer;
    QVector<TrainGraphicsView*> traindisp;

    // network
    QTcpSocket *socket;

private slots:
    // ui
    void slot_timeout();
    void on_calendarWidget_clicked(const QDate &date);
    void on_pushButton_clicked(); // inqury
    void stack0();
    void stack1();
    void on_logInButton_clicked();
    void on_createAccountButton_clicked();

    // network
    void slot_readyRead();
    void slot_disconnect();
};
#endif // TRAINTICKETSYSTEMCLIENT_H
