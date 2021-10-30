#include "screenshot_ui.h"
#include "ui_screenshot_ui.h"

screenshot_UI::screenshot_UI(QWidget *parent, QString name) :
    QWidget(parent),
    ui(new Ui::screenshot_UI)
{
    beginx = 0;
    beginy = 0;
    endx = 0;
    endy = 0;
    shutmode = false;
    tname = name;
    QScreen *screen = QGuiApplication::primaryScreen();
    image = QPixmap();
    if(screen)
    {
        image = screen->grabWindow(0);
    }
    //screen->grabWindow(0).save("test.jpg");
    ui->setupUi(this);
    this->ui->label->resize(screen->size());

    this->ui->label->setPixmap(image.scaled(screen->size()));
}

screenshot_UI::~screenshot_UI()
{
    delete ui;
}

void screenshot_UI::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
            this->hide();
            break;
    }
}

void screenshot_UI::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<event->x()<<"\n"<<event->y();
    switch(event->button())
    {
        case Qt::LeftButton:
            beginx = event->x();
            beginy = event->y();
            shutmode = true;
            update();
            break;
        case Qt::RightButton:
            this->hide();
            break;
    }
}

void screenshot_UI::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug()<<event->x()<<"\n"<<event->y();
    endx = event->x();
    endy = event->y();
    update();
}

void screenshot_UI::mouseReleaseEvent(QMouseEvent *event)
{
    endx = event->x();
    endy = event->y();
    shutmode = false;
    //update();
    QPixmap pimage = QPixmap(image).copy(qMin(beginx, endx), qMin(beginy, endy), qAbs(beginx-endx), qAbs(beginy-endy));
    pimage.save(tname);
    this->hide();
}

void screenshot_UI::paintEvent(QPaintEvent *event)
{
    //QLabel::paintEvent(event);
    QPixmap pimage;
    pimage = image;
    QScreen *screen = QGuiApplication::primaryScreen ();
    pimage = pimage.scaled(screen->size());
    QPainter paint(&pimage);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    paint.setPen(pen);

    if(shutmode)
    {
        paint.drawLine(beginx, beginy, beginx, endy);
        paint.drawLine(beginx, beginy, endx, beginy);
        paint.drawLine(beginx, endy, endx, endy);
        paint.drawLine(endx, beginy, endx, endy);
    }

    this->ui->label->setPixmap(pimage.scaled(screen->size()));
}
