#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include<QDebug>
#include<QWidget>
#include<QTcpServer>
#include<QNetworkInterface>
#include<QMessageBox>
#include<QTcpSocket>

using namespace std;

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
    void on_freshen_clicked();

    void oneProcessNewConnection();
    void oneProcessAcceptError(QAbstractSocket::SocketError err);
    void oneProcessDisconnected();
    void oneProcessReadyRead();
    void oneProcessConnected();
    void del_connect();

    void on_clientlist_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
    QTcpServer *myServer;
    QList<QTcpSocket *> arrayClient;
    QTcpSocket *client;

    void InitServe();
};
#endif // MAINWINDOW_H
