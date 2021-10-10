#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitSocket();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitSocket()
{
    myClient = new QTcpSocket(this);
    myClient->bind(QHostAddress("127.0.0.1"), 12345);
}

void MainWindow::on_connect_clicked()
{
    QString serveIP = this->ui->serverip->text();
    QString servePort = this->ui->serverport->text();
    myClient->connectToHost(QHostAddress(serveIP), servePort.toInt());
    connect(myClient, SIGNAL(connected()), this, SLOT(oneProcessConnected()));
    connect(myClient, SIGNAL(readyRead()), this, SLOT(oneProcessReadyRead()));
    connect(myClient, SIGNAL(disconnected()), this, SLOT(oneProcessDisconnected()));
    connect(myClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(oneProcessError(QAbstractSocket::SocketError)));
}

void MainWindow::oneProcessConnected()
{
    QString msg = "连接成功！\n";
    this->ui->information->append(msg);
}

void MainWindow::oneProcessReadyRead()
{
    QString msg, str1, str2;
    while(!myClient->atEnd())
        str2.append(QString(myClient->readAll()));
    this->ui->information->append(str2);
}

void MainWindow::oneProcessDisconnected()
{
    QString msg = "服务器退出\n";
    this->ui->information->append(msg);
}

void MainWindow::oneProcessError(QAbstractSocket::SocketError err)
{
    qDebug()<<err;
}

void MainWindow::on_send_clicked()
{
    QString msg = this->ui->message->toPlainText();
    int ret = myClient->write(msg.toUtf8());
    if(ret <= 0)
        return;
    this->ui->information->append("你说：\n"+msg);
    this->ui->message->clear();
}
