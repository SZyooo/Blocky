#include "blockwidget.h"

#include<QLabel>
#include<QFont>
#include<QFontMetrics>
#include<QPainter>
#include <QPen>
#include "inputwidget.h"
#include "tool.h"
#include "commonvalue.h"
#include <QMouseEvent>
#include <QDrag>
#include "blockmimedata.h"

BlockWidget::BlockWidget(QString op, QString des, const vector<QString> &params, QColor color)
    :_operation_label(new QLabel(this)),_op_name(op),_toolTip(des),_color(color),
      _params_str(params)
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
        InputWidget* iw = new InputWidget;
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
        _params.push_back({label,iw});
    }
    hei += 2*EDGE;
    mid = hei / 2;
    Resize();
    ChangeBKG(this,_color);
    setMouseTracking(true);
    setToolTip(_toolTip);
    _pressed = false;
    _accept_drag = true;
}

BlockWidget::BlockWidget(const BlockWidget &bw)
{
    _operation_label = new QLabel(bw._operation_label->text(),this);
    _operation_label->setFont(bw._operation_label->font());
    _operation_label->setGeometry(bw._operation_label->geometry());

    _op_name = bw._op_name;
    _toolTip = bw._toolTip;
    for(int i=0;i<bw._params.size();i++){
        QLabel* label = new QLabel(bw._params[i].first->text(),this);
        label->setFont(bw._params[i].first->font());
        InputWidget *iw = new InputWidget;
        iw->setParent(this);
        label->setGeometry(bw._params[i].first->geometry());
        this->_params.push_back({label,iw});
    }
    mid = bw.mid;
    Resize();
    _color = bw._color;
    ChangeBKG(this,_color);
    this->setMouseTracking(true);
    this->setToolTip(_toolTip);
    _pressed = false;
    _accept_drag = true;
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

QColor BlockWidget::GetBackgoundColor() const
{
    return _color;
}

void BlockWidget::SetAcceptDrag(bool draggable)
{
    _accept_drag = draggable;
}

void BlockWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton && _accept_drag){
        _press_pos.setX((int)e->position().x());
        _press_pos.setY((int)e->position().y());
        _pressed = true;
    }
    return QWidget::mousePressEvent(e);
}

void BlockWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(_pressed && _accept_drag){
        int x = (int)event->position().x();
        int y = (int)event->position().y();
        QPoint pos(x,y);
        int move_dis = (pos - _press_pos).manhattanLength();
        if(move_dis > DRAG_THRESHOLD){
            QDrag* drag = new QDrag(this);
            BlockMimeData* mimeData = new BlockMimeData(_op_name,_toolTip,_params_str);
            drag->setMimeData(mimeData);
            drag->exec();
        }
    }

    return QWidget::mousePressEvent(event);
}

void BlockWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        _pressed = false;
    }
    return QWidget::mouseReleaseEvent(e);
}

void BlockWidget::Resize()
{
    int wid = 0;
    _operation_label->move(EDGE,mid - _operation_label->height()/2);
    wid = _operation_label->x() + _operation_label->width();
    for(int i=0;i<_params.size();i++){
        wid += SPACE;
        int x = wid;
        int y = mid - _params[i].first->height()/2;
        _params[i].first->move(x,y);
        wid = _params[i].first->x() + _params[i].first->width() + SPACE;
        x = wid;
        y = mid - _params[i].second->height() / 2;
        _params[i].second->move(x,y);
        wid = _params[i].second->x() + _params[i].second->width();
    }
    wid +=  EDGE;
    this->resize(wid + EDGE,mid*2);
}

void BlockWidget::SelectVar()
{
    int idx = -1;
    for(int i=0;i<_params.size();i++){
        if(_params[i].second == sender()){
            idx = i;
            break;
        }
    }
    if(idx == -1 || idx == _params.size())
        return;
    _values[idx] = _params[idx].second->FetchValue();
    _is_var[idx] = true;
}

void BlockWidget::InputVal(const QString &s)
{
    int idx = -1;
    for(int i=0;i<_params.size();i++){
        if(_params[i].second == sender()){
            idx = i;
            break;
        }
    }
    if(idx == -1 || idx == _params.size())
        return;
    _values[idx] = s;
    _is_var[idx] = false;
}
