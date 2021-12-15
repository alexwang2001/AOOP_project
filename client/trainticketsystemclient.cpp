#include "trainticketsystemclient.h"
#include "ui_trainticketsystemclient.h"

TrainTicketSystemClient::TrainTicketSystemClient(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TrainTicketSystemClient)
{
    ui->setupUi(this);

    // network
    socket = new QTcpSocket;
    socket->connectToHost(QHostAddress::LocalHost,13579);
    if(!socket->waitForConnected(1000)){
        ui->statusbar->showMessage("can't connect to server すみません");
    }
    else
        ui->statusbar->showMessage("connecting to server 안녕하세요");

    connect(socket, &QTcpSocket::readyRead, this, &TrainTicketSystemClient::slot_readyRead);
    connect(socket, &QTcpSocket::disconnected, this, &TrainTicketSystemClient::slot_disconnect);

    // set datetime
    datetime = new QDateTime;

    // set timer
    timer = new QTimer;
    timer->setInterval(5000);
    timer->start();
    connect(timer, SIGNAL(timeout()), this, SLOT(slot_timeout()));

    // set initial page
    switchPage(1);
    set_login_page();
    ui->lineEdit_account->setText("TsaiMother");
    ui->lineEdit_password->setText("111111");



    // set inqury time
    ui->dateEdit->setDate(datetime->currentDateTime().date());
    ui->calendarWidget->setDateEditEnabled(0);
    ui->comboBox_6->setCurrentIndex(1);
    ui->comboBox_7->setCurrentIndex(8);

    // disp pages use
    connect(ui->actionstack0,SIGNAL(triggered()),this,SLOT(stack0()));
    connect(ui->actionstack1,SIGNAL(triggered()),this,SLOT(stack1()));

    // train time table
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(0);



}

TrainTicketSystemClient::~TrainTicketSystemClient()
{
    delete ui;
}

//=========================================================
//================ time shown in statusbar ================

void TrainTicketSystemClient::slot_timeout()
{
    QString show = "";
    QDate date = datetime->currentDateTime().date();
    show += QString::number(date.year()) + "/" + QString::number(date.month()) + "/" + QString::number(date.day());
    show += "  ";
    QTime time = datetime->currentDateTime().time();
    if(time.hour() > 9)
        show += QString::number(time.hour())+ ":";
    else
        show += "0" + QString::number(time.hour())+ ":";
    if(time.minute() > 9)
        show += QString::number(time.minute())+ ":";
    else
        show += "0" + QString::number(time.minute())+ ":";
    if(time.second() > 9)
        show += QString::number(time.second());
    else
        show += "0" + QString::number(time.second());
    ui->statusbar->showMessage(show);

    timer->setInterval(1000);
}


//============================================================
//================ calender of train schedule ================

void TrainTicketSystemClient::on_calendarWidget_clicked(const QDate &date)
{
    ui->dateEdit->setDate(date);
}


//============================================================
//================ inqury of train schedule ==================

void TrainTicketSystemClient::on_pushButton_clicked()
{
    QString dep = ui->comboBox->currentText();
    QString arr = ui->comboBox_2->currentText();

    int start = (ui->comboBox_3->currentIndex()*12)*100+(ui->comboBox_4->currentIndex()+1)*100+ui->comboBox_5->currentIndex()*10;
    int end = (ui->comboBox_6->currentIndex()*12)*100+(ui->comboBox_7->currentIndex()+1)*100+ui->comboBox_8->currentIndex()*10;
    QString stnum = QString::number(start);
    QString ednum = QString::number(end);
    QDate date = ui->dateEdit->date();
    QString datestr;
    switch (date.dayOfWeek()) {
        case 1:
            datestr = "mon";
            break;
        case 2:
            datestr = "tue";
            break;
        case 3:
            datestr = "wed";
            break;
        case 4:
            datestr = "thu";
            break;
        case 5:
            datestr = "fri";
            break;
        case 6:
            datestr = "sat";
            break;
        case 7:
            datestr = "sun";
            break;
    }
    qDebug() << "Inqury: " << dep << arr << stnum << ednum;

    // socket request
    request(ClientOrder::TrainInquiry);
    request(ui->radioButton->isChecked()?"1":"0");
    request(datestr);
    request(ednum);
    request(stnum);
    request(arr);
    request(dep);
    send_request(socket);

    // clear table
    for(int i=0; i<traindisp.size(); i++){
        ui->tableWidget->removeCellWidget(i,0);
        ui->tableWidget->removeRow(i);
    }

    // clear train display table
    traindisp.clear();
}


//============================================================
//========================= set pages ========================

void TrainTicketSystemClient::switchPage(int idx){
    ui->stackedWidget->setCurrentIndex(idx);
}

void TrainTicketSystemClient::stack0(){
    switchPage(0);
}

void TrainTicketSystemClient::stack1(){
    switchPage(1);
}


//============================================================
//========================= login ============================

void TrainTicketSystemClient::on_logInButton_clicked()
{
    if(ui->logInButton->text()=="Back")
        set_login_page();

    else{
        ui->label_account_being_used->setVisible(false);
        ui->label_passwords_too_short->setVisible(false);

        QString acc = ui->lineEdit_account->text();
        QString pas = ui->lineEdit_password->text();

        request(QString::number(ClientOrder::Login) + "\n" + acc + "\n" + pas);
        send_request(socket);
    }
}


void TrainTicketSystemClient::set_login_page(){
    ui->label_confirm_password->setVisible(false);
    ui->lineEdit_confirm_password->setVisible(false);
    ui->label_join_us->setVisible(false);
    ui->logInButton->setVisible(true);
    ui->createAccountButton->setText("Create Account");
    ui->label_account_being_used->setVisible(false);
    ui->label_passwords_not_the_same->setVisible(false);
    ui->label_passwords_too_short->setVisible(false);
    ui->logInButton->setText("Login");
}


//============================================================
//===================== create account =======================

void TrainTicketSystemClient::set_create_client_account_page(){
    ui->label_account_being_used->clear();
    ui->label_passwords_too_short->clear();
    ui->lineEdit_account->clear();
    ui->lineEdit_password->clear();
    ui->lineEdit_confirm_password->clear();
    ui->createAccountButton->setText("Confirm :)");
    ui->label_confirm_password->setVisible(true);
    ui->lineEdit_confirm_password->setVisible(true);
    ui->logInButton->setText("Back");
    ui->label_join_us->setVisible(true);
}

void TrainTicketSystemClient::set_create_staff_account_age(){

}

void TrainTicketSystemClient::on_createAccountButton_clicked()
{
    bool error=0;
    QString password_text, confirm_password_text;

    if(ui->createAccountButton->text()=="Create Account")
        set_create_client_account_page();
    else {
        ui->label_passwords_not_the_same->setVisible(false);
        ui->label_passwords_too_short->setVisible(false);
        ui->label_account_being_used->setVisible(false);

        if(ui->lineEdit_account->text()==""){
            ui->label_account_being_used->setText("Please enter your account :)");
            ui->label_account_being_used->setVisible(true);
            error=1;
        }

        if(ui->lineEdit_password->text().length()<6){
            ui->label_passwords_too_short->setText("passwords must be at least 6\ncharacters :(");
            ui->label_passwords_too_short->setVisible(true);
            password_text=ui->lineEdit_password->text();
            confirm_password_text=ui->lineEdit_confirm_password->text();
            ui->lineEdit_password->clear();
            ui->lineEdit_confirm_password->clear();
            error=1;
        }

        if(password_text != confirm_password_text){
            ui->label_passwords_not_the_same->setText("Passwords must be the same :(");
            ui->label_passwords_not_the_same->setVisible(true);
            ui->lineEdit_confirm_password->clear();
            error=1;
        }

        if(error==1) return;
        Client client;
        client.setAccount(ui->lineEdit_account->text());
        client.setNewPassword(ui->lineEdit_password->text());
        /*if(server->newClient(client) == 1) {
            ui->label_account_being_used->setText("This account has been used :(");
            ui->label_account_being_used->setVisible(true);
            return;
        }*/
        ui->lineEdit_password->clear();
        set_login_page();
    }
}


//============================================================
//========================== Network =========================

void TrainTicketSystemClient::slot_readyRead(){
    QTcpSocket *socket = dynamic_cast<QTcpSocket*>(sender());

    QString req;
    USI order;
    while(socket->canReadLine()){
        req = response(socket->readLine());
        order = req.toUShort();

        if(order == ServerOrder::AssignPort){
            req = response(socket->readLine());
            port = req.toUShort();
            qDebug() << "connect to port " << port;
        }
        else if(order == ServerOrder::StatusbarMessage){
            req = response(socket->readLine());
            ui->statusbar->showMessage(req);
        }
        else if(order == ServerOrder::ConnectionReject){

        }
        else if(order == ServerOrder::LoginStatus){
            req = response(socket->readLine());
            USI login_status = req.toUInt();
            if(login_status == People::ACCOUNTWRONG){
                ui->label_account_being_used->setVisible(true);
                ui->label_account_being_used->setText("Didnt find your account :(");
            }
            else if(login_status == People::PASSWORDWRONG){
                ui->label_passwords_too_short->setText("Opps, wrong password :(");
                ui->label_passwords_too_short->setVisible(true);
            }
            else{
                QMessageBox::about(this, "WELCOME", "Successfully loged in :)");
                switchPage(0);
                set_station_table();
            }
        }
        else if(order == ServerOrder::SendStationTable){
            req = response(socket->readLine());
            while(req != QString::number(ServerOrder::DataTransferEnd)){
                ui->comboBox->addItem(req);
                ui->comboBox_2->addItem(req);
                req = response(socket->readLine());
            }
            // set station combobox
            ui->comboBox_2->setCurrentIndex(1);
        }
        else if(order == ServerOrder::SendTrainInquiry){

            QString data = response(socket->readLine());
            int i=0;
            while(data != QString::number(ServerOrder::DataTransferEnd)){
                TrainGraphicsView *item = new TrainGraphicsView(nullptr);
                traindisp.push_back(item);
                int trainno = data.toInt();
                QString dep = response(socket->readLine());
                QString arr = response(socket->readLine());
                int dept = response(socket->readLine()).toInt();
                int arrt = response(socket->readLine()).toInt();

                item->TrainInquryView(trainno,dep,arr,dept,arrt);

                ui->tableWidget->setRowCount(++i);
                ui->tableWidget->setCellWidget(i-1, 0, item);
                ui->tableWidget->setColumnWidth(i-1, 380);
                ui->tableWidget->setRowHeight(i-1, 120);
                ui->tableWidget->verticalScrollMode();

                connect(item, &TrainGraphicsView::BuyTicketClicked, this, &TrainTicketSystemClient::slot_booking);

                data = response(socket->readLine());

            }
        }
    }
}

void TrainTicketSystemClient::slot_disconnect(){
    socket->deleteLater();
}

//============================================================
//===================== Train Inqury Page ====================

void TrainTicketSystemClient::set_station_table(){
    request(QString::number(ClientOrder::AskStationTable));
    send_request(socket);
}

void TrainTicketSystemClient::slot_booking(){
    TrainGraphicsView *item = dynamic_cast<TrainGraphicsView*>(sender());

    ui->label_13->setText(QString::number(item->trainNum));
    ui->label_15->setText(item->dep);
    ui->label_16->setText(item->termi);
    ui->label_17->setText("200");
    switchPage(2);
}



//============================================================
//======================= Booking Page =======================

//book
void TrainTicketSystemClient::on_pushButton_2_clicked()
{

}

//cancel
void TrainTicketSystemClient::on_pushButton_3_clicked()
{
    switchPage(0);
}

