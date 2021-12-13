#include "networkclient.h"

NetworkClient::NetworkClient() {

    // set port
    port = 12345;

    // get client's IP address
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost){
             IP = address.toString();
             break;
        }
    }

    // Tcp socket
    socket = new QTcpSocket;
}

bool NetworkClient::connectToServer(){
    // Tcp socket
    socket->connectToHost(QHostAddress::LocalHost,port);
    if(!socket->waitForConnected(1000)){
        qDebug() << "can't connect to server";
        return false;
    }
    else
        qDebug() << "successful connect to" << socket->peerAddress().toString();

    QObject::connect(socket, &QTcpSocket::readyRead, this, &NetworkClient::slot_readyRead);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &NetworkClient::slot_disconnect);

    socket->write(QByteArray(IP.toUtf8()));

    return true;
}

bool NetworkClient::login(QString account, QString password){
    QString req = IP + "/" + "login" + "/" + account + "/" + password;
    requestToServer(req);
    if(!socket->waitForReadyRead(1000))
        return false;
    if(response == "s")
        return true;
    else
        return false;
}

void NetworkClient::newManagerRequest(Manager manager, QString key){
    QString req = IP + "/" + "newManager" + "/" + manager.getAccount() + "/" + manager.getPassword() + "/" + key;
    requestToServer(req);
}

void NetworkClient::newStaffRequest(Staff staff, QString key){
    QString req = IP + "/" + "newStaff" + "/" + staff.getAccount() + "/" + staff.getPassword() + "/" + key;
    requestToServer(req);
}

void NetworkClient::newClientRequest(Client client){
    QString req = IP + "/" + "newClient" + "/" + client.getAccount() + "/" + client.getPassword() + "/";
    requestToServer(req);
}

void NetworkClient::requestToServer(QString req){
    socket->write(QByteArray(req.toUtf8()));
}

void NetworkClient::slot_readyRead(){
    QByteArray bytes =  socket->readLine().trimmed();
    QString str = QString::fromUtf8(bytes);
    response = str;
}

void NetworkClient::slot_disconnect(){

}
