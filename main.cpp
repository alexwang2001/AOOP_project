#include "ticketsalessystem.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TicketSalesSystem w;
    w.show();
    return a.exec();
}
