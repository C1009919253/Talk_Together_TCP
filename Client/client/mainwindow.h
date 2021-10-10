#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QDebug>
#include<QWidget>
#include<QTcpServer>
#include<QNetworkInterface>
#include<QMessageBox>
#include<QTcpSocket>

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

private:
    Ui::MainWindow *ui;
    QTcpSocket *myClient;
    void InitSocket();
};
#endif // MAINWINDOW_H
