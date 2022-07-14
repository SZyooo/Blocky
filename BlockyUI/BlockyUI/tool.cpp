

#include "tool.h"
#include <QString>
#include<QColor>
#include <QWidget>
#include <QPalette>
#include <QGraphicsDropShadowEffect>
#include "commonvalue.h"
#include <vector>


using std::vector;
#ifdef BDEBUG
#include <QDebug>
#endif
void Debug(QString s){
#ifdef BDEBUG
    qDebug()<<s;
#endif
}

void ChangeBKG(QWidget *w, QColor c)
{
    QPalette p = w->palette();
    p.setColor(QPalette::Window,c);
    w->setAutoFillBackground(true);
    w->setPalette(p);
}
void TurnOnShadowEffect(QWidget * w)
{
    QGraphicsDropShadowEffect * effect = new QGraphicsDropShadowEffect;
    effect->setOffset(0, 0);//设置阴影距离
    effect->setColor(QColor(0,0,0,90));//设置阴影颜色
    effect->setBlurRadius(15);//设置阴影圆角
    w->setGraphicsEffect(effect);
}

void TurnOffShadowEffect(QWidget *w)
{
    w->setGraphicsEffect(nullptr);
}

void SetRadius(QWidget *w, int pix)
{
    w->setStyleSheet(QString("{border-top-left-radius:%1 px}").arg(pix));
}


QColor FetchAColor()
{
    static int idx = 0;
    size_t size = RandomColors.size();
    return RandomColors[(idx++)%size];
}
