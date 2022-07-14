#include "segmentcontainerwidget.h"

#include "loopsegmentwidget.h"
#include "commonvalue.h"
#include "tool.h"
#include <cmath>
#include <QEvent>
#include <QHoverEvent>
using std::max;
SegmentContainerWidget::SegmentContainerWidget()
    :_add_button(),_del_button()
    ,_inner_widget(),_delBtn_hovering(-1)
{
    _add_button.resize(ADDBUTTON_WIDTH,ADDBUTTON_HEIGHT);
    _add_button.setText("+");

    QFont font;
    font.setPointSize(max(ADDBUTTON_WIDTH,ADDBUTTON_HEIGHT));
    _add_button.setFont(font);
    _del_button.resize(DELBUTTON_WIDTH,DELBUTTON_HEIGHT);
    _del_button.setText("X");
    font.setPointSize(max(DELBUTTON_HEIGHT,DELBUTTON_WIDTH));
    _del_button.setFont(font);
    setWidget(&_inner_widget);
    _add_button.setParent(&_inner_widget);
    _del_button.setParent(&_inner_widget);
    connect(&_add_button,&QPushButton::clicked,this,&SegmentContainerWidget::AddSegment);
    connect(&_del_button,&QPushButton::clicked,this,&SegmentContainerWidget::RemoveSegment);
    setAttribute(Qt::WA_Hover,true);
    setMouseTracking(true);
    installEventFilter(this);
    Redraw();
}

SegmentContainerWidget::~SegmentContainerWidget()
{
    _add_button.setParent(nullptr);
    _del_button.setParent(nullptr);
    _inner_widget.setParent(nullptr);
}

void SegmentContainerWidget::AddSegment()
{
    LoopSegmentWidget* lsw = new LoopSegmentWidget;
    lsw->setParent(&_inner_widget);
    ChangeBKG(lsw,SEGMENT_BKG);
    TurnOnShadowEffect(lsw);
    lsw->show();
    _segments.push_back(lsw);
    Redraw();
}

void SegmentContainerWidget::RemoveSegment()
{
    if(_delBtn_hovering!=-1){
        LoopSegmentWidget* lsw = _segments[_delBtn_hovering];
        _segments.erase(_segments.begin() + _delBtn_hovering);
        delete lsw;
        _delBtn_hovering = -1;
        DisableDelButton();
        Redraw();
    }
}

void SegmentContainerWidget::Redraw()
{
    int w = width() - 2*EDGE;
    int x = EDGE;
    int y = EDGE;
    int h = LoopSegmentWidget::EDIT_WIDGET_HEIGHT;
    for(int i=0;i<_segments.size();i++){
        _segments[i]->move(x,y);
        _segments[i]->resize(w,h);
        y = _segments[i]->y() + h + SPACING;
    }
    //Add button
    x = (width() - ADDBUTTON_WIDTH) / 2;
    y = y + (LoopSegmentWidget::EDIT_WIDGET_HEIGHT - ADDBUTTON_HEIGHT) / 2;
    _add_button.move(x,y);
    h = (_segments.size()+1)*LoopSegmentWidget::EDIT_WIDGET_HEIGHT
            + _segments.size()*SPACING + 2*EDGE;
    _inner_widget.setGeometry(0,0,w,h);
    DisableDelButton();
}

void SegmentContainerWidget::resizeEvent(QResizeEvent *e)
{
    Redraw();
    return QScrollArea::resizeEvent(e);
}

bool SegmentContainerWidget::eventFilter(QObject *o, QEvent *e)
{
    if(e->type() == QEvent::HoverMove){
        QHoverEvent* he = static_cast<QHoverEvent*>(e);
        int x = (int)he->position().x();
        int y = (int)he->position().y();
        int idx = GetSegmentIndexByMouseLocalPos(x,y);
        Debug(QString::number(idx));
        _delBtn_hovering = idx;
        if(idx != -1){
            ShowDelButtonAt(idx);
        }
        else{
            DisableDelButton();
        }
    }
    return QScrollArea::eventFilter(o,e);
}

void SegmentContainerWidget::ShowDelButtonAt(int idx)
{
    EnableDelButton();
    int x = _segments[idx]->x() + _segments[idx]->width() - DELBUTTON_WIDTH;
    int y = 0;
    _del_button.move(x,y);
}

int SegmentContainerWidget::GetSegmentIndexByMouseLocalPos(int x, int y)
{
    int res = -1;
    for(int i=0;i<_segments.size();i++){
        if(_segments[i]->geometry().contains(x,y)){
            res = i;
            break;
        }
    }
    return res;
}

void SegmentContainerWidget::DisableDelButton()
{
    _del_button.setEnabled(false);
    _del_button.setVisible(false);
}

void SegmentContainerWidget::EnableDelButton()
{
    _del_button.setEnabled(true);
    _del_button.setVisible(true);
    _del_button.raise();
}
