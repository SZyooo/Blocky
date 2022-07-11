#include "blockwidget.h"

#include<QLabel>
#include<QFont>
#include<QFontMetrics>
#include<QPainter>
#include <QPen>
#include "inputwidget.h"
#include "tool.h"
#include "commonvalue.h"

BlockWidget::BlockWidget(QString op, QString des, const vector<QString> &params, AREA area)
    :_operation_label(new QLabel(this)),_op_name(op),_toolTip(des),_area(area)
{
    int wid = EDGE,hei = 0;
    mid = 0;
    QFont font;
    font.setPointSize(FONTSIZE);
    QFontMetrics fm(font);
    QSize size = fm.boundingRect(op).size();
    _operation_label->setText(_op_name);
    _operation_label->setFont(font);
    _operation_label->resize(size);
    wid += size.width() + SPACE;
    for(int i=0;i<params.size();i++){
        QLabel* label = new QLabel(params[i],this);
        label->setFont(font);
        InputWidget* iw = new InputWidget({});
        iw->setParent(this);
        QSize s = fm.boundingRect(params[i]).size();
        if(hei < s.height())  {
            hei = fm.boundingRect(params[i]).height();
        }
        label->resize(s);
        label->move(wid,EDGE);
        wid += s.width() + 2;
        iw->move(wid,EDGE);
        wid += iw->width() + SPACE;
        this->_params.push_back({label,iw});
    }
    hei += 2*EDGE;
    mid = hei / 2;
    _operation_label->move(EDGE,mid - _operation_label->height()/2);
    for(int i=0;i<_params.size();i++){
        int x = _params[i].first->x();
        int y = mid - _params[i].first->height()/2;
        _params[i].first->move(x,y);
        x = _params[i].second->x();
        y = mid - _params[i].second->height() / 2;
        _params[i].second->move(x,y);
    }
    this->resize(wid + EDGE,hei);
    ChangeBKG(this,&BLOCK_COLOR);
    this->setMouseTracking(true);
    this->setToolTip(_toolTip);
}

void BlockWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int x = _operation_label->x() + _operation_label->width() + EDGE/2;
    int top = EDGE;
    int bottom = width() - EDGE;
    painter.drawLine(QPointF(x,top),QPointF(x,bottom));
    for(int i=0;i<_params.size()-1;i++){
        x = _params[i].second->x() + _params[i].second->width() + EDGE/2;
        painter.drawLine(QPointF(x,top),QPointF(x,bottom));
    }
}
