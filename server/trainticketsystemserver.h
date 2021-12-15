#ifndef TRAINTICKETSYSTEMSERVER_H
#define TRAINTICKETSYSTEMSERVER_H

#include <QMainWindow>
#include <QObject>
#include <QString>
#include <QMap>
#include <QList>
#include <QSqlDatabase>
#include <QSqlResult>
#include <QSqlQuery>
#include <QSqlError>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include <QStandardItemModel>
#include <../people.h>
#include <../databasesystem.h>
#include <../trainticketsystem.h>

QT_BEGIN_NAMESPACE
namespace Ui { class TrainTicketSystemServer; }
QT_END_NAMESPACE

class TrainTicketSystemServer : public QMainWindow, public TrainTicketSystem
{
    Q_OBJECT

public:
    TrainTicketSystemServer(QWidget *parent = nullptr);
    ~TrainTicketSystemServer();

private:
    Ui::TrainTicketSystemServer *ui;

    // initial system
    bool connectDB(QString hostname, QString username, QString password, USI port, USI max);

    // database
    DatabaseSystem dbsystem;

    // server network
    QTcpServer *server;

    // sockets
    QMap<USI,QTcpSocket*> sockets; // <port, socket>
    USI PORTMAX = 2;


    QMap<USI,USI> usertype; // <port,Usertype> check order.h

    // table
    QStandardItemModel *model;
    static int tableRowCnt;
    void writeinTable(USI port, USI usertype, QString content);

    // login
    int login(const QString& account, const QString& password, const USI& port);

    // send station table
    void sendSationTable(QTcpSocket* socket);
    void searchTrain(bool depOrarr, const QString& depart, const QString& arrive, const QString& starttime, const QString& endtime, const QString& dayoftheweek, QTcpSocket* socket);

    // set pages
    void switchPage(int idx);


public slots:
    void slot_newConnection();
    void slot_readyRead();
    void slot_disconnect();


private slots:
    void on_pushButton_clicked();

};
#endif // TRAINTICKETSYSTEMSERVER_H
