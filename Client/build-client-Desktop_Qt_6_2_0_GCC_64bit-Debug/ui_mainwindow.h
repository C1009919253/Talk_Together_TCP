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
    QPushButton *send;
    QPushButton *select_image;
    QPushButton *screenshot;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *serverip;
    QPushButton *connect;
    QLabel *label_3;
    QLineEdit *serverport;
    QLabel *label_4;
    QLineEdit *nickname;
    QTextBrowser *information;
    QTextEdit *message;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 691);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        send = new QPushButton(centralwidget);
        send->setObjectName(QString::fromUtf8("send"));
        send->setGeometry(QRect(590, 590, 141, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font.setPointSize(16);
        send->setFont(font);
        select_image = new QPushButton(centralwidget);
        select_image->setObjectName(QString::fromUtf8("select_image"));
        select_image->setGeometry(QRect(450, 590, 141, 41));
        select_image->setFont(font);
        screenshot = new QPushButton(centralwidget);
        screenshot->setObjectName(QString::fromUtf8("screenshot"));
        screenshot->setGeometry(QRect(310, 590, 141, 41));
        screenshot->setFont(font);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font1.setPointSize(20);
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        serverip = new QLineEdit(centralwidget);
        serverip->setObjectName(QString::fromUtf8("serverip"));

        gridLayout->addWidget(serverip, 0, 1, 1, 2);

        connect = new QPushButton(centralwidget);
        connect->setObjectName(QString::fromUtf8("connect"));
        connect->setFont(font);

        gridLayout->addWidget(connect, 0, 3, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 1, 0, 1, 2);

        serverport = new QLineEdit(centralwidget);
        serverport->setObjectName(QString::fromUtf8("serverport"));

        gridLayout->addWidget(serverport, 1, 2, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font1);

        gridLayout->addWidget(label_4, 2, 0, 1, 2);

        nickname = new QLineEdit(centralwidget);
        nickname->setObjectName(QString::fromUtf8("nickname"));

        gridLayout->addWidget(nickname, 2, 2, 1, 1);

        information = new QTextBrowser(centralwidget);
        information->setObjectName(QString::fromUtf8("information"));

        gridLayout->addWidget(information, 3, 0, 1, 4);

        message = new QTextEdit(centralwidget);
        message->setObjectName(QString::fromUtf8("message"));

        gridLayout->addWidget(message, 4, 0, 1, 4);

        MainWindow->setCentralWidget(centralwidget);
        message->raise();
        label_3->raise();
        connect->raise();
        send->raise();
        information->raise();
        serverport->raise();
        label->raise();
        serverip->raise();
        select_image->raise();
        label_4->raise();
        nickname->raise();
        screenshot->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
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
        send->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\357\274\201", nullptr));
        select_image->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        screenshot->setText(QCoreApplication::translate("MainWindow", "\346\210\252\345\233\276", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250ip\357\274\232", nullptr));
        connect->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\357\274\201", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250port\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\230\265\347\247\260\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
