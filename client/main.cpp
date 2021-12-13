#include "trainticketsystemclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrainTicketSystemClient w;
    w.show();
    return a.exec();
}
