#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QDebug>
#include<QWidget>
#include<QTcpServer>
#include<QNetworkInterface>
#include<QMessageBox>
#include<QTcpSocket>
#include<QByteArray>
#include<QThread>
#include<QFileDialog>
#include<QString>
#include<QByteArray>
#include<QBuffer>

#include"screenshot_ui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connect_clicked();
    void on_send_clicked();
    void oneProcessConnected();
    void oneProcessReadyRead();
    void oneProcessDisconnected();
    void oneProcessError(QAbstractSocket::SocketError err);

    void on_select_image_clicked();

    void on_screenshot_clicked();

    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::MainWindow *ui;
    QTcpSocket *myClient;
    QString TS;
    int mode;
    QString image_html;
    QString image;

    void InitSocket();
    QString ImgPathToHtml(QString path);
    QImage Base64TOImage(const QString &data);
    QByteArray ImageToBase64(const QImage &image);
};
#endif // MAINWINDOW_H
