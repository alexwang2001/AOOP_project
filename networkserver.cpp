#include "networkserver.h"

NetworkServer::NetworkServer() {

    // set database
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setDatabaseName("trainsystem");
    database.setUserName("root");
    database.setPassword("qzp,wxom");
    database.setPort(3306);

    // set query
    query = new QSqlQuery;
    *query = QSqlQuery(database);
}

NetworkServer::~NetworkServer() {
    delete query;
    database.close();
}

int NetworkServer::newManager(Manager manager){
    for(Manager each_manager: managerlist)
        if(manager.getAccount()==each_manager.getAccount()) return NameExist;
    managerlist.push_back(manager);
    return NoError;
}

int NetworkServer::newClient(Client client){
    QString name = client.getAccount();
    QString password = client.getPassword();
    query->exec("select * from account where Account = '" + name + "';");
    if(query->next())
        return NameExist;
    else
        query->exec("insert into account values('" + name + "','" + password + "', 'Client');");
    qDebug() << query->lastError();
    return NoError;
}

int NetworkServer::newStaff(Staff staff){
    for(Staff each_staff: stafflist)
        if(staff.getAccount()==each_staff.getAccount()) return NameExist;
    stafflist.push_back(staff);
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
