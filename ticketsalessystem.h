#ifndef TICKETSALESSYSTEM_H
#define TICKETSALESSYSTEM_H

#include <QMainWindow>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QLabel>
#include <QDebug>
#include <QSqlError>
#include <QVector>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QGraphicsView>
#include "networkserver.h"
#include "mygraphicview.h"


QT_BEGIN_NAMESPACE
namespace Ui { class TicketSalesSystem; }
QT_END_NAMESPACE

class TicketSalesSystem : public QMainWindow
{
    Q_OBJECT

public:
    explicit TicketSalesSystem(QWidget *parent = nullptr);
    ~TicketSalesSystem();

    void switchPage(int idx);
    void set_login_page();
    void set_create_client_account_page();
    void set_create_staff_account_age();

private:
    Ui::TicketSalesSystem *ui;

    QDateTime *datetime;
    QTimer *timer;
    NetworkServer *server;


private slots:
    void slot_timeout();
    void on_calendarWidget_clicked(const QDate &date);
    void on_pushButton_clicked();
    void stack0();
    void stack1();
    void on_logInButton_clicked();
    void on_createAccountButton_clicked();
};
#endif // TICKETSALESSYSTEM_H
