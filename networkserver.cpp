#include "networkserver.h"

NetworkServer::NetworkServer() {


}

NetworkServer::~NetworkServer() {

}

int NetworkServer::newManager(Manager manager, QString key){
    if(key != "4321")
        return NoAuthority;
    QString name = manager.getAccount();
    QString password = manager.getPassword();
    databasesystem->query()->exec("select * from account where Account = '" + name + "';");
    if(databasesystem->query()->next())
        return NameExist;
    else
        databasesystem->query()->exec("insert into account values('" + name + "','" + password + "', 'Manager');");
    qDebug() << databasesystem->query()->lastError();
    return NoError;
}

int NetworkServer::newStaff(Staff staff, QString key){
    if(key != "1234")
        return NoAuthority;
    QString name = staff.getAccount();
    QString password = staff.getPassword();
    databasesystem->query()->exec("select * from account where Account = '" + name + "';");
    if(databasesystem->query()->next())
        return NameExist;
    else
        databasesystem->query()->exec("insert into account values('" + name + "','" + password + "', 'Staff');");
    qDebug() << databasesystem->query()->lastError();
    return NoError;
}

int NetworkServer::newClient(Client client){
    QString name = client.getAccount();
    QString password = client.getPassword();
    databasesystem->query()->exec("select * from account where Account = '" + name + "';");
    if(databasesystem->query()->next())
        return NameExist;
    else
        databasesystem->query()->exec("insert into account values('" + name + "','" + password + "', 'Client');");
    qDebug() << databasesystem->query()->lastError();
    return NoError;
}

bool NetworkServer::findClinet(QString account, Client& log_in_client){
    for(Client client: clientlist){
        if(client.getAccount() == account){
            log_in_client=client;
            return 1;
        }
    }
    return 0;
}

void NetworkServer::slot_newConnection(){
    QTcpSocket *socket = server->nextPendingConnection();

    QByteArray writebytes = QString("connection successful").toUtf8();
    socket->write(writebytes);

    sockets.insert(socket->peerAddress().toIPv4Address(), socket);

    QObject::connect(socket, &QTcpSocket::readyRead, this, &NetworkServer::slot_readyRead);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &NetworkServer::slot_disconnect);
}

void NetworkServer::slot_readyRead(){
    QTcpSocket *socket = dynamic_cast<QTcpSocket*>(sender());
    qDebug() << "reading" << QString::fromUtf8(socket->readAll());
}
