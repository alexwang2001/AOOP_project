#include "trainticketsystem.h"

TrainTicketSystem::TrainTicketSystem() {
    request_string = "";
}


void TrainTicketSystem::request(const QString &re){
    request_string += re + "\n";
}

void TrainTicketSystem::request(const int &renum){
    request_string += QString::number(renum) + "\n";
}

void TrainTicketSystem::send_request(QTcpSocket *socket){
    QByteArray writebyte = (request_string).toUtf8();
    socket->write(writebyte);
    qDebug() << "writing" << request_string;
    request_string = "";
}

QString TrainTicketSystem::response(const QByteArray& request){
    QString str = QString::fromUtf8(request.trimmed());
    qDebug() << "reading" << str;
    return str;
}

QString TrainTicketSystem::usertypeStr(int n){
    switch (n) {
        case 0:
            return "Guest";
            break;
        case 1:
            return "Client";
            break;
        case 2:
            return "Staff";
            break;
        case 3:
            return "Manager";
            break;
    }
    return "Alien";
}
