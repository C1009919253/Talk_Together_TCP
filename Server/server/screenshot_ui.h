#ifndef SCREENSHOT_UI_H
#define SCREENSHOT_UI_H

#include <QWidget>
#include<QScreen>
#include<QKeyEvent>
#include<QDebug>
#include<QMouseEvent>
#include<QPaintEvent>
#include<QPainter>
#include<QPaintEngine>
#include<QPixmap>

namespace Ui {
class screenshot_UI;
}

class screenshot_UI : public QWidget
{
    Q_OBJECT

public:
    explicit screenshot_UI(QWidget *parent = nullptr);
    ~screenshot_UI();

private:
    Ui::screenshot_UI *ui;
    int beginx;
    int beginy;
    int endx;
    int endy;
    QPixmap image;
    bool shutmode;

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);
};

#endif // SCREENSHOT_UI_H
