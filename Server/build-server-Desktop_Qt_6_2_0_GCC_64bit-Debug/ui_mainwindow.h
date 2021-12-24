/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QLabel *text_serverip;
    QLineEdit *serverip;
    QLabel *text_clientip;
    QLineEdit *clientip;
    QLabel *usersonline;
    QPushButton *freshen;
    QLabel *text_serverport;
    QLineEdit *serverport;
    QLabel *text_clientport;
    QLineEdit *clientport;
    QListWidget *clientlist;
    QPushButton *connect;
    QTextBrowser *information;
    QTextEdit *message;
    QPushButton *screenshot;
    QPushButton *select_image;
    QPushButton *send;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1136, 721);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        text_serverip = new QLabel(centralwidget);
        text_serverip->setObjectName(QString::fromUtf8("text_serverip"));
        QFont font;
        font.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font.setPointSize(20);
        text_serverip->setFont(font);

        gridLayout_4->addWidget(text_serverip, 0, 0, 1, 1);

        serverip = new QLineEdit(centralwidget);
        serverip->setObjectName(QString::fromUtf8("serverip"));

        gridLayout_4->addWidget(serverip, 0, 1, 1, 2);

        text_clientip = new QLabel(centralwidget);
        text_clientip->setObjectName(QString::fromUtf8("text_clientip"));
        text_clientip->setFont(font);

        gridLayout_4->addWidget(text_clientip, 0, 3, 1, 3);

        clientip = new QLineEdit(centralwidget);
        clientip->setObjectName(QString::fromUtf8("clientip"));

        gridLayout_4->addWidget(clientip, 0, 6, 1, 3);

        usersonline = new QLabel(centralwidget);
        usersonline->setObjectName(QString::fromUtf8("usersonline"));
        usersonline->setFont(font);

        gridLayout_4->addWidget(usersonline, 0, 9, 1, 1);

        freshen = new QPushButton(centralwidget);
        freshen->setObjectName(QString::fromUtf8("freshen"));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font1.setPointSize(14);
        freshen->setFont(font1);

        gridLayout_4->addWidget(freshen, 0, 10, 1, 1);

        text_serverport = new QLabel(centralwidget);
        text_serverport->setObjectName(QString::fromUtf8("text_serverport"));
        text_serverport->setFont(font);

        gridLayout_4->addWidget(text_serverport, 1, 0, 1, 2);

        serverport = new QLineEdit(centralwidget);
        serverport->setObjectName(QString::fromUtf8("serverport"));

        gridLayout_4->addWidget(serverport, 1, 2, 1, 1);

        text_clientport = new QLabel(centralwidget);
        text_clientport->setObjectName(QString::fromUtf8("text_clientport"));
        text_clientport->setFont(font);

        gridLayout_4->addWidget(text_clientport, 1, 3, 1, 4);

        clientport = new QLineEdit(centralwidget);
        clientport->setObjectName(QString::fromUtf8("clientport"));

        gridLayout_4->addWidget(clientport, 1, 7, 1, 2);

        clientlist = new QListWidget(centralwidget);
        clientlist->setObjectName(QString::fromUtf8("clientlist"));
        clientlist->setContextMenuPolicy(Qt::CustomContextMenu);

        gridLayout_4->addWidget(clientlist, 1, 9, 5, 2);

        connect = new QPushButton(centralwidget);
        connect->setObjectName(QString::fromUtf8("connect"));
        connect->setFont(font1);

        gridLayout_4->addWidget(connect, 2, 1, 1, 2);

        information = new QTextBrowser(centralwidget);
        information->setObjectName(QString::fromUtf8("information"));

        gridLayout_4->addWidget(information, 3, 0, 1, 9);

        message = new QTextEdit(centralwidget);
        message->setObjectName(QString::fromUtf8("message"));

        gridLayout_4->addWidget(message, 4, 0, 2, 9);

        screenshot = new QPushButton(centralwidget);
        screenshot->setObjectName(QString::fromUtf8("screenshot"));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font2.setPointSize(16);
        screenshot->setFont(font2);

        gridLayout_4->addWidget(screenshot, 5, 4, 1, 1);

        select_image = new QPushButton(centralwidget);
        select_image->setObjectName(QString::fromUtf8("select_image"));
        select_image->setFont(font2);

        gridLayout_4->addWidget(select_image, 5, 5, 1, 3);

        send = new QPushButton(centralwidget);
        send->setObjectName(QString::fromUtf8("send"));
        send->setFont(font2);

        gridLayout_4->addWidget(send, 5, 8, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        message->raise();
        text_serverip->raise();
        text_clientip->raise();
        text_serverport->raise();
        text_clientport->raise();
        serverip->raise();
        clientip->raise();
        serverport->raise();
        clientport->raise();
        connect->raise();
        send->raise();
        information->raise();
        usersonline->raise();
        clientlist->raise();
        freshen->raise();
        select_image->raise();
        screenshot->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1136, 28));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        text_serverip->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250ip\357\274\232", nullptr));
        text_clientip->setText(QCoreApplication::translate("MainWindow", "\345\256\242\346\210\267\347\253\257ip\357\274\232", nullptr));
        usersonline->setText(QCoreApplication::translate("MainWindow", "\345\234\250\347\272\277\347\224\250\346\210\267\357\274\232", nullptr));
        freshen->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260\357\274\201", nullptr));
        text_serverport->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250port\357\274\232", nullptr));
        text_clientport->setText(QCoreApplication::translate("MainWindow", "\345\256\242\346\210\267\347\253\257port\357\274\232", nullptr));
        connect->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250\346\234\215\345\212\241\345\231\250\357\274\201", nullptr));
        screenshot->setText(QCoreApplication::translate("MainWindow", "\346\210\252\345\233\276", nullptr));
        select_image->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        send->setText(QCoreApplication::translate("MainWindow", "   \345\217\221\351\200\201\357\274\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
