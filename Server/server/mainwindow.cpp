#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitServe();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitServe()
{
    myServer = new QTcpServer(this);
}

void MainWindow::on_connect_clicked()
{
    QString myAddr = this->ui->serverip->text();
    QString myPort = this->ui->serverport->text();
    QString msg;
    bool ret = myServer->listen(QHostAddress(myAddr), myPort.toUInt());
    if(!ret)
    {
        msg = "绑定失败！\n";
        this->ui->information->setText(msg);
        return;
    }
    else
    {
        msg = "绑定成功！\n";
        this->ui->connect->setEnabled(false);
        this->ui->information->setText(msg);
    }
    int MAXNUM = 100;
    myServer->setMaxPendingConnections(MAXNUM);
    connect(myServer, SIGNAL(newConnection()), this, SLOT(oneProcessNewConnection()));
    connect(myServer, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(oneProcessAcceptError(QAbstractSocket::SocketError)));
}

void MainWindow::oneProcessNewConnection()
{
    client = myServer->nextPendingConnection();
    arrayClient.append(client);
    connect(client, SIGNAL(disconnected()), this, SLOT(oneProcessDisconnected()));
    connect(client, SIGNAL(readyRead()), this, SLOT(oneProcessReadyRead()));
    connect(client, SIGNAL(connected()), this, SLOT(oneProcessConnected()));
    QString msg = QString("客户端[%1:%2] 连入！\n").arg(client->peerAddress().toString()).arg(client->peerPort());
    this->ui->information->append(msg);
    on_freshen_clicked();
}

void MainWindow::oneProcessAcceptError(QAbstractSocket::SocketError err)
{
    qDebug()<<err;
}

void MainWindow::oneProcessDisconnected()
{
    QTcpSocket *client = (QTcpSocket *)this->sender();
    QString msg = QString("客户端[%1:%2]   退出！\n").arg(client->peerAddress().toString()).arg(client->peerPort());
    this->ui->information->append(msg);
    for(int i = 0; i < arrayClient.length(); i++)
    {
        if(arrayClient.at(i)->peerAddress() == client->peerAddress())
            if(arrayClient.at(i)->peerPort() == client->peerPort())
            {
                arrayClient.removeAt(i);
                break;
            }
    }
    on_freshen_clicked();
}

void MainWindow::oneProcessReadyRead()
{
    QTcpSocket *client = (QTcpSocket *)this->sender();
    QString str1 = QString("客户端[%1:%2] 说：\n").arg(client->peerAddress().toString()).arg(client->peerPort());
    QString msg;
    QString str2;
    while(!client->atEnd())
        msg.append(QString(client->readAll()));
    str2 = QString("%1%2").arg(str1).arg(msg);
    this->ui->information->append(str2);
    for(int i = 0; i < arrayClient.length(); i++) // 收到的信息发送给其他客户端
        if(arrayClient.at(i)->peerAddress().toString() != client->peerAddress().toString() || arrayClient.at(i)->peerPort() != client->peerPort())
        {
            arrayClient.at(i)->write(str2.toUtf8());
            ui->message->clear();
        }
}

void MainWindow::oneProcessConnected()
{
    QTcpSocket *client = (QTcpSocket *)this->sender();
    /*QString msg = QString("客户端[%1:%2] 连入！\n").arg(client->peerAddress().toString()).arg(client->peerPort());
    this->ui->information->append(msg);
    QMessageBox::information(NULL, "Title", "Content");*/
}

void MainWindow::on_send_clicked()
{
    QString ip = ui->clientip->text();
    QString port = ui->clientport->text();
    QString msg = this->ui->message->toPlainText();
    this->ui->information->append("你说：\n" + msg);
    QString fro = "后台程序员大爷说：\n"+msg;
    for(int i = 0; i < arrayClient.length(); i++)
        if(ip == "" || arrayClient.at(i)->peerAddress().toString() == ip)
            if(port == "" || arrayClient.at(i)->peerPort() == port.toUInt())
            {
                arrayClient.at(i)->write(fro.toUtf8());
                ui->message->clear();
            }
}

void MainWindow::on_freshen_clicked()
{
    this->ui->clientlist->clear();
    for(int i = 0; i < arrayClient.length(); i++)
    {
        QString lis = QString("客户端[%1:%2]").arg(arrayClient.at(i)->peerAddress().toString()).arg(arrayClient.at(i)->peerPort());
        this->ui->clientlist->addItem(lis);
        this->ui->clientlist->item(i)->setForeground(QBrush(QColor(Qt::white)));
        this->ui->clientlist->item(i)->setBackground(QColor(70, 153, 181));
        this->ui->clientlist->item(i)->setFont(QFont("隶书", 12, QFont::Bold));
        this->ui->clientlist->item(i)->setSizeHint(QSize(20, 50));
        this->ui->clientlist->item(i)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_clientlist_customContextMenuRequested(const QPoint &pos)
{
    QListWidgetItem *curItem = this->ui->clientlist->itemAt(pos);
    if(curItem == NULL)
        return;
    QMenu *popMenu = new QMenu(this);
    QAction *delconnect = new QAction("断开连接", this);
    popMenu->addAction(delconnect);
    connect(delconnect, SIGNAL(triggered()), this, SLOT(del_connect()));
    popMenu->exec(QCursor::pos());
    delete popMenu;
    delete delconnect;
}

void MainWindow::del_connect()
{
    QListWidgetItem *item = this->ui->clientlist->currentItem();
    QString l = item->text();
    QString ip = "", port = "";
    for(int i = 0; i < l.length(); i++)
    {
        if(l[i] == '[')
            while(l[i] != ':')
            {
                i++;
                ip += l[i];
            }
        if(l[i] == ':')
            while(l[i] != ']')
            {
                i++;
                port += l[i];
            }
    }
    ip = ip.left(ip.length()-1);
    port = port.left(port.length()-1);
    for(int i = 0; i < arrayClient.length(); i++)
        if(ip == arrayClient.at(i)->peerAddress().toString() && port.toUInt() == arrayClient.at(i)->peerPort())
        {
            arrayClient.at(i)->write("由于您的恶劣行径，您被伟大的后台大爷关闭了连接");
            arrayClient.at(i)->close(); // 断开连接！！！！！！！！！！老子就是后台！！！！！！！！
            break;
        }
}
