

#include "tool.h"
#include <QString>
#include<QColor>
#include <QWidget>
#include <QPalette>
#ifdef BDEBUG
#include <QDebug>
#endif
void Debug(QString s){
#ifdef BDEBUG
    qDebug()<<s;
#endif
}

void ChangeBKG(QWidget *w, QColor *c)
{
    QPalette p = w->palette();
    p.setColor(QPalette::Window,*c);
    w->setPalette(p);
}
