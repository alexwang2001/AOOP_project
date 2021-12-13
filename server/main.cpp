#include "trainticketsystemserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TrainTicketSystemServer w;
    w.show();
    return a.exec();
}
