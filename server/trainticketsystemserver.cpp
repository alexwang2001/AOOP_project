#include "trainticketsystemserver.h"
#include "ui_trainticketsystemserver.h"

TrainTicketSystemServer::TrainTicketSystemServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrainTicketSystemServer)
{
    ui->setupUi(this);

    // set Tcp server
    server = new QTcpServer;
    server->listen(QHostAddress::Any, 13579);

    // check server is listening
    if(!server->isListening())
        ui->statusbar->showMessage("server is not listening", 5000);

    connect(server, &QTcpServer::newConnection, this, &TrainTicketSystemServer::slot_newConnection);

    // table
    model = new QStandardItemModel(0,3,ui->tableView);

    model->setHorizontalHeaderItem(0,new QStandardItem(QString("Client Number")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QString("User Identity")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QString("Request")));

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,100);

    ui->tableView->setColumnWidth(2,578);

    // connect DB page
    ui->stackedWidget->setCurrentIndex(1);
    ui->lineEdit->setText("140.113.138.72");
    ui->lineEdit_2->setText("client");
    ui->lineEdit_3->setText("tsaimotheriloveyou");
    ui->lineEdit_4->setText("3306");
    ui->lineEdit_5->setText("2");

}

TrainTicketSystemServer::~TrainTicketSystemServer()
{
    delete ui;
}


// ==========================================================
// ==================== Database ============================

bool TrainTicketSystemServer::connectDB(QString hostname, QString username, QString password, USI port, USI max){
    // set max connection
    PORTMAX = max;

    // set database
    dbsystem.initializeDB(hostname, username, password, port);

    // check database is open
    if(dbsystem.database().isOpen()){
        ui->statusbar->showMessage("conection success 안녕하세요!!", 10000);
        switchPage(0);
        return true;
    }
    else
        ui->statusbar->showMessage("connection fail すみません!!", 10000);
    return false;
}

void TrainTicketSystemServer::on_pushButton_clicked()
{
    connectDB(ui->lineEdit->text(),ui->lineEdit_2->text(),ui->lineEdit_3->text(),ui->lineEdit_4->text().toUShort(),ui->lineEdit_5->text().toUShort());
}

int TrainTicketSystemServer::tableRowCnt = 0;

// ==========================================================
// ==================== Network =============================

void TrainTicketSystemServer::slot_newConnection(){
    QTcpSocket *socket = server->nextPendingConnection();

    request(QString::number(StatusbarMessage)+"\nConnection Successful 안녕하세요");
    writeinTable(0,GUEST,"Ask for connection");

    // check empty port
    QList keylist = sockets.keys();
    for(int i = 1; i <= PORTMAX; i++){
        if(keylist.empty()){
            // assign port
            request(QString::number(AssignPort)+"\n"+QString::number(i));
            send_request(socket);
            sockets.insert(i, socket);
            usertype.insert(i, GUEST);

            // connect to slot
            connect(socket, &QTcpSocket::readyRead, this, &TrainTicketSystemServer::slot_readyRead);
            connect(socket, &QTcpSocket::disconnected, this, &TrainTicketSystemServer::slot_disconnect);
            break;
        }
        else if(keylist.first() != i){
            // assign port
            request(QString::number(AssignPort)+"\n"+QString::number(i));
            send_request(socket);
            sockets.insert(i, socket);
            usertype.insert(i, GUEST);

            // connect to slot
            connect(socket, &QTcpSocket::readyRead, this, &TrainTicketSystemServer::slot_readyRead);
            connect(socket, &QTcpSocket::disconnected, this, &TrainTicketSystemServer::slot_disconnect);
            break;
        }
        else if(i == PORTMAX){
            request(QString::number(StatusbarMessage)+"\nConnection Full 죄송합니다");
            request(QString::number(ConnectionReject));
            send_request(socket);
            socket->deleteLater();
            break;
        }
        keylist.erase(keylist.constBegin());
    }

}

void TrainTicketSystemServer::slot_readyRead(){
    QTcpSocket *socket = dynamic_cast<QTcpSocket*>(sender());
    QString req;
    if(socket->canReadLine()){
        req = response(socket->readLine());
        USI order = req.toUShort();

        port = sockets.key(socket); // serch port
        USI identity = *usertype.find(port); // search identity(user type)
        writeinTable(port,identity,req);

        if(order == ClientOrder::Login){
            QString account = response(socket->readLine());
            QString password = response(socket->readLine());
            int verify = login(account,password,port);
            request(QString::number(LoginStatus)+"\n"+QString::number(verify));
            send_request(socket);
        }
        else if(order == ClientOrder::AskStationTable){
            sendSationTable(socket);
        }
        else if(order == ClientOrder::TrainInquiry){
            bool depOrarr = QString::fromUtf8(socket->readLine()).toInt();
            searchTrain(depOrarr,response(socket->readLine()),response(socket->readLine()),response(socket->readLine()),response(socket->readLine()),response(socket->readLine()),socket);
        }
    }

}

void TrainTicketSystemServer::slot_disconnect(){
    QTcpSocket *socket = dynamic_cast<QTcpSocket*>(sender());
    writeinTable(sockets.key(socket),*usertype.constFind(sockets.key(socket)), "Disconnect");

    sockets.remove(sockets.key(socket));
    usertype.remove(sockets.key(socket));

    qDebug() << socket->peerAddress().toString() << " disconnect";
    socket->deleteLater();
}

// ==========================================================
// ================= Train display Table ====================


void TrainTicketSystemServer::writeinTable(USI port, USI usertype, QString content){

    model->setVerticalHeaderItem(tableRowCnt,new QStandardItem(QString::number(tableRowCnt+1)));
    model->setItem(tableRowCnt, 0,new QStandardItem(QString::number(port)));
    model->setItem(tableRowCnt, 1,new QStandardItem(usertypeStr(usertype)));
    model->setItem(tableRowCnt, 2,new QStandardItem(content));
    tableRowCnt++;
}

// ==========================================================
// ====================== Login =============================

int TrainTicketSystemServer::login(const QString& account, const QString& password, const USI& port){
    People people;
    people.setAccount(account);
    people.setNewPassword(password);


    QSqlQuery* query = dbsystem.query();
    query->exec("select * from account where Account = '" + account +"';");

    // verifying
    if(!query->next()){
        return People::ACCOUNTWRONG;
    }

    else if(People::PASSWORDWRONG == people.accountVerify(query->value(0).toString(), query->value(1).toString())){
         return People::PASSWORDWRONG;
    }

    // search identity
    QString identity = query->value(2).toString();
    if(identity == "Client"){
        *usertype.find(port) = CLIENT;
        writeinTable(port, CLIENT,"Login");
    }
    else if(identity == "Staff"){
        *usertype.find(port) = STAFF;
        writeinTable(port, STAFF,"Login");
    }
    else if(identity == "Manager"){
        *usertype.find(port) = MANAGER;
        writeinTable(port, MANAGER,"Login");
    }

    return People::BOTHRIGHT;
}

// ==========================================================
// ============= Station & Train Searching ==================

void TrainTicketSystemServer::sendSationTable(QTcpSocket* socket){
    writeinTable(port, *usertype.find(port), "Ask for station table");

    request(ServerOrder::SendStationTable);

    QSqlQuery* query = dbsystem.query();
    query->exec("select * from stationtable;");
    while(query->next()){
        request(query->value(0).toString());
        qDebug() << query->value(0).toString();
    }
    request(ServerOrder::DataTransferEnd);
    send_request(socket);
}

void TrainTicketSystemServer::searchTrain(bool depOrarr, const QString &depart, const QString &arrive, const QString &starttime, const QString &endtime, const QString &dayoftheweek, QTcpSocket* socket){
    writeinTable(port, *usertype.find(port), "Train Inquiry");

    request(ServerOrder::SendTrainInquiry);

    QSqlQuery* query = dbsystem.query();
    if(depOrarr){
        query->exec("select * from traintable where Departure = '" + depart + "' and Terminal = '" + arrive + "' and DepartureTime >= " + starttime + " and DepartureTime <= " + endtime + " and " + dayoftheweek + " = 1;");
        qDebug() << "select * from traintable where Departure = '" + depart + "' and Terminal = '" + arrive + "' and DepartureTime >= " + starttime + " and DepartureTime <= " + endtime + " and " + dayoftheweek + " = 1;";
        qDebug() << query->lastError();
    }
    else{
        query->exec("select * from traintable where Departure = '" + depart + "' and Terminal = '" + arrive + "' and ArrivalTime >= " + starttime + " and ArrivalTime <= " + endtime + " and '" + dayoftheweek + "' = 1;");
        qDebug() << "select * from traintable where Departure = '" + depart + "' and Terminal = '" + arrive + "' and ArrivalTime >= " + starttime + " and ArrivalTime <= " + endtime + " and '" + dayoftheweek + "' = 1;";
        qDebug() << query->lastError();
    }

    while(query->next()){
        for(int i=0; i<=4; i++){
            request(query->value(i).toString());
        }
    }
    request(ServerOrder::DataTransferEnd);
    send_request(socket);
}


//============================================================
//========================= set pages ========================

void TrainTicketSystemServer::switchPage(int idx){
    ui->stackedWidget->setCurrentIndex(idx);
}

