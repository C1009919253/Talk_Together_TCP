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
    //myClient->bind(QHostAddress("127.0.0.1"), 12345);
    TS = "";
    mode = 0;
    image = "";
    image_html = "";
    QDir *creatdir = new QDir;
    if(!creatdir->exists("cache"))
        creatdir->mkdir("cache");
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
    QString str;
    while(!myClient->atEnd())
        str.append(QString(myClient->readAll()));
    if(str == "" || str == "ok")
        return;
    if(str == "###commonbegin###")
    {
        TS = "";
        myClient->write("ok");
        mode = 1; // 开始接受
        return;
    }
    if(mode == 1)
    {
        if(str.contains("###commonend###"))
        {
            str = str.replace("###commonend###", "");
            mode = 0;
            TS.append(str);
            this->ui->information->append(TS);
            TS = "";
            myClient->write("ok");
            return;
        }
        TS.append(str);
    }
    if(str == "###imagebegin###")
    {
        TS = "";
        myClient->write("ok");
        mode = 2; // 开始接受
        return;
    }
    if(mode == 2)
    {
        if(str.contains("###imageend###"))
        {
            str = str.replace("###imageend###", "");
            mode = 0;
            TS.append(str);
            QImage image = Base64TOImage(TS);
            QString cache= "cache/" + QDateTime::currentDateTime().toString("yyyy-MM-ddHH-mm-ss")  + ".jpg";
            image.save(cache, "JPG", -1);
            QString img_html = ImgPathToHtml(cache);
            this->ui->information->append(img_html);
            //this->ui->information->append(TS);
            TS = "";
            myClient->write("ok");
            return;
        }
        TS.append(str);
    }
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
    QString fro2 = "";
    QString nickname = this->ui->nickname->text();
    myClient->write("###commonbegin###");
    myClient->waitForReadyRead();
    if(nickname == "")
        nickname = "某不愿透露姓名的同学";
    myClient->write(nickname.toUtf8()+"说：\n"+msg.toUtf8()+"###commonend###");
    //myClient->write("###commonend###");
    myClient->waitForReadyRead();
    if(image != "" && image_html != "")
    {
        QImage img(image);
        //this->ui->information->append(QString(ImageToBase64(img)));
        //fro = fro + "###image###"+QString(ImageToBase64(img));
        fro2 = QString(ImageToBase64(img));
        myClient->write("###imagebegin###");
        myClient->waitForReadyRead();
        myClient->write(fro2.toUtf8());
        myClient->write("###imageend###");
        myClient->waitForReadyRead();
    }
    this->ui->information->append("你说：\n"+msg);
    this->ui->information->append(image_html);
    this->ui->information->append("\n");
    this->ui->message->clear();
    this->image = "";
    this->image_html = "";
}

QImage MainWindow::Base64TOImage(const QString &data)
{
    QByteArray imageData = QByteArray::fromBase64(data.toLatin1());
    QImage image;
    image.loadFromData(imageData);
    return image;
}

QString MainWindow::ImgPathToHtml(QString path)
{
    path = QString("<img src=\"%1\"/>").arg(path); // 转换为Html
    return path;
}

void MainWindow::on_select_image_clicked()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(QStringLiteral("选择图片"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("File(*.jpg)"));
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

QByteArray MainWindow::ImageToBase64(const QImage &image)
{
    QByteArray imageData;
    QBuffer buffer(&imageData);
    image.save(&buffer, "jpg");
    imageData = imageData.toBase64();
    return imageData;
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

