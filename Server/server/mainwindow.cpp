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
    this->ui->text_clientip->setText(tr("客户端 ip："));
    this->ui->text_serverip->setText(tr("服务器 ip："));
    this->ui->text_clientport->setText(tr("客户端 port："));
    this->ui->text_serverport->setText(tr("服务器 port："));
    image_html = "";
    image = "";
    TS = "";
    mode = 0;
    QDir *creatdir = new QDir;
    if(!creatdir->exists("cache"))
        creatdir->mkdir("cache");
    this->ui->message->installEventFilter(this);
    this->ui->clientip->installEventFilter(this);
    this->ui->clientport->installEventFilter(this);
    this->ui->serverip->installEventFilter(this);
    this->ui->serverport->installEventFilter(this);
}

void MainWindow::on_connect_clicked()
{
    QString myAddr = this->ui->serverip->text();
    QString myPort = this->ui->serverport->text();
    QString msg;
    bool ret = myServer->listen(QHostAddress(myAddr), myPort.toUInt());
    if(!ret)
    {
        msg = tr("绑定失败！\n");
        this->ui->information->setText(msg);
        return;
    }
    else
    {
        msg = tr("绑定成功！\n");
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
    QString msg = QString(tr("客户端[%1:%2] 连入！\n")).arg(client->peerAddress().toString()).arg(client->peerPort());
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
    QString msg = QString(tr("客户端[%1:%2]   退出！\n")).arg(client->peerAddress().toString()).arg(client->peerPort());
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
    QString str1 = QString(tr("客户端[%1:%2] 说：")).arg(client->peerAddress().toString()).arg(client->peerPort());
    //this->ui->information->append(str1);
    QString msg = "";
    QString str2;
    while(!client->atEnd())
        msg.append(QString(client->readAll()));
    if(msg == "" || msg == "ok")
        return;
    for(int i = 0; i < arrayClient.length(); i++) // 收到的信息发送给其他客户端
        if(arrayClient.at(i)->peerAddress().toString() != client->peerAddress().toString() || arrayClient.at(i)->peerPort() != client->peerPort())
        {
            //arrayClient.at(i)->write("###commonbegin###");
            //arrayClient.at(i)->waitForReadyRead();
            //arrayClient.at(i)->write(str1.toUtf8()+"###commonend###");
            //arrayClient.at(i)->waitForReadyRead();
            arrayClient.at(i)->write(msg.toUtf8());
            //arrayClient.at(i)->waitForReadyRead();
        }
    if(msg == "###commonbegin###")
    {
        TS = "";
        client->write("ok");
        mode = 1; // 开始接受
        return;
    }
    if(mode == 1)
    {
        if(msg.contains("###commonend###"))
        {
            msg = msg.replace("###commonend###", "");
            mode = 0;
            TS.append(msg);
            //this->ui->information->append(str1);
            this->ui->information->append(TS);
            TS = "";
            client->write("ok");
            return;
        }
        TS.append(msg);
    }
    if(msg == "###imagebegin###")
    {
        TS = "";
        client->write("ok");
        mode = 2; // 开始接受
        return;
    }
    if(mode == 2)
    {
        if(msg.contains("###imageend###"))
        {
            msg = msg.replace("###imageend###", "");
            mode = 0;
            TS.append(msg);
            QImage image = Base64TOImage(TS);
            QString cache= "cache/" + QDateTime::currentDateTime().toString("yyyy-MM-ddHH-mm-ss")  + ".jpg";
            // cache = "cache/cache.jpg";
            image.save(cache, "JPG", -1);
            QString img_html = ImgPathToHtml(cache);
            // this->ui->information->append(str1);
            this->ui->information->append(img_html);
            //this->ui->information->append(TS);
            TS = "";
            client->write("ok");
            return;
        }
        TS.append(msg);
    }
    //str2 = QString("%1%2").arg(str1).arg(msg);
    //this->ui->information->append(str2);
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
    this->ui->information->append(tr("你说：\n") + msg + "\n");
    QString fro = tr("后台程序员大爷说：\n")+msg+"\n";
    QString fro2 = "";
    if(image_html != "" && image != "")
    {
        //this->ui->information->append(image_html);
        QImage img(image);
        //this->ui->information->append(QString(ImageToBase64(img)));
        //fro = fro + "###image###"+QString(ImageToBase64(img));
        fro2 = QString(ImageToBase64(img));
        this->ui->information->append(image_html);
    }
    for(int i = 0; i < arrayClient.length(); i++)
        if(ip == "" || arrayClient.at(i)->peerAddress().toString() == ip)
            if(port == "" || arrayClient.at(i)->peerPort() == port.toUInt())
            {
                arrayClient.at(i)->write("###commonbegin###");
                arrayClient.at(i)->waitForReadyRead();
                arrayClient.at(i)->write(fro.toUtf8());
                //arrayClient.at(i)->waitForReadyRead();
                arrayClient.at(i)->write("###commonend###");
                arrayClient.at(i)->waitForReadyRead();
                if(image_html != "" && image != "")
                {
                    arrayClient.at(i)->write("###imagebegin###");
                    arrayClient.at(i)->waitForReadyRead();
                    arrayClient.at(i)->write(fro2.toUtf8());
                    //arrayClient.at(i)->waitForReadyRead();
                    arrayClient.at(i)->write("###imageend###");
                    arrayClient.at(i)->waitForReadyRead();
                }
                //ui->message->clear();
            }
    this->ui->message->clear();
    image_html = "";
    image = "";
}

void MainWindow::on_freshen_clicked()
{
    this->ui->clientlist->clear();
    for(int i = 0; i < arrayClient.length(); i++)
    {
        QString lis = QString(tr("客户端[%1:%2]")).arg(arrayClient.at(i)->peerAddress().toString()).arg(arrayClient.at(i)->peerPort());
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
    QAction *delconnect = new QAction(tr("断开连接"), this);
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
            QString clomsg = tr("由于您的恶劣行径，您被伟大的后台大爷关闭了连接");
            arrayClient.at(i)->write(clomsg.toUtf8());
            arrayClient.at(i)->close(); // 断开连接！！！！！！！！！！老子就是后台！！！！！！！！
            break;
        }
}

void MainWindow::on_select_image_clicked()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(QStringLiteral("select image"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter("File(*.jpg)");
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if (fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    if(fileNames.length() <= 0)
        return;
    image = fileNames[0];
    image_html = ImgPathToHtml(fileNames[0]);
    this->ui->message->append(image_html);
}

QString MainWindow::ImgPathToHtml(QString path)
{
    path = QString("<img src=\"%1\"/>").arg(path); // 转换为Html
    return path;
}

QByteArray MainWindow::ImageToBase64(const QImage &image)
{
    QByteArray imageData;
    QBuffer buffer(&imageData);
    image.save(&buffer, "jpg");
    imageData = imageData.toBase64();
    return imageData;
}

QImage MainWindow::Base64TOImage(const QString &data)
{
    QByteArray imageData = QByteArray::fromBase64(data.toLatin1());
    QImage image;
    image.loadFromData(imageData);
    return image;
}

void MainWindow::on_screenshot_clicked()
{
    //QPixmap::grabWindow(QApplication::desktop()->winId()).save("123","jpg");
    QString cache= "cache/" + QDateTime::currentDateTime().toString("yyyy-MM-ddHH-mm-ss")  + ".jpg";
    screenshot_UI *scs;
    scs = new screenshot_UI(nullptr, cache);
    scs->showFullScreen();
    scs->setWindowModality(Qt::ApplicationModal);
    scs->show();
    image = cache;
    image_html = ImgPathToHtml(image);
    this->ui->message->append(image_html);
}

/*void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        this->on_send_clicked();
    }
}*/

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this->ui->message)
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
            {
                this->on_send_clicked();
                return true;
            }
        }

    if(watched == this->ui->clientip || watched == this->ui->clientport || watched == this->ui->serverip || watched == this->ui->serverport)
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
            {
                this->on_connect_clicked();
                return true;
            }
        }

    return false;
}
