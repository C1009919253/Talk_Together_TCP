/********************************************************************************
** Form generated from reading UI file 'screenshot_ui.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENSHOT_UI_H
#define UI_SCREENSHOT_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_screenshot_UI
{
public:
    QLabel *label;

    void setupUi(QWidget *screenshot_UI)
    {
        if (screenshot_UI->objectName().isEmpty())
            screenshot_UI->setObjectName(QString::fromUtf8("screenshot_UI"));
        screenshot_UI->resize(400, 300);
        label = new QLabel(screenshot_UI);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 67, 17));

        retranslateUi(screenshot_UI);

        QMetaObject::connectSlotsByName(screenshot_UI);
    } // setupUi

    void retranslateUi(QWidget *screenshot_UI)
    {
        screenshot_UI->setWindowTitle(QCoreApplication::translate("screenshot_UI", "Form", nullptr));
        label->setText(QCoreApplication::translate("screenshot_UI", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class screenshot_UI: public Ui_screenshot_UI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENSHOT_UI_H
