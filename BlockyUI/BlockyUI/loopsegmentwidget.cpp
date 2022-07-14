#include "loopsegmentwidget.h"
#include <QPushButton>
#include <editwidget.h>
#include <tool.h>
#include <QEvent>
#include <QHoverEvent>
#include "tool.h"

LoopSegmentWidget::LoopSegmentWidget()
    :_add_button(new QPushButton),_inner_widget(new QWidget),_remove_button(new QPushButton)
    ,_del_btn_hovering_wgt(-1)
{
    _add_button->setParent(_inner_widget);
    _add_button->setText("--ADD--");
    _remove_button->setText("X");
    _remove_button->setParent(this);
    _remove_button->resize(DELBUTTON_WIDTH,DELBUTTON_HEIGHT);
    DisabledRemoveBtn();
    setWidget(_inner_widget);
    AddBranch();
    connect(_add_button,&QPushButton::clicked,this,&LoopSegmentWidget::AddBranch);
    connect(_remove_button,&QPushButton::clicked,this,&LoopSegmentWidget::RemoveBranch);
    setAttribute(Qt::WA_Hover,true);
    installEventFilter(this);
    setFixedHeight(EDIT_WIDGET_HEIGHT + EDGE * 4);
}

void LoopSegmentWidget::resizeEvent(QResizeEvent *e)
{
    return QWidget::resizeEvent(e);
}

void LoopSegmentWidget::AddBranch()
{
    EditWidget* wgt = new EditWidget;
    wgt->setParent(_inner_widget);
    wgt->resize(EDIT_WIDGET_WIDTH,EDIT_WIDGET_HEIGHT);
    wgt->SetCondition("1",EQUAL,"1");
    _edit_widgets.push_back(wgt);
    TurnOnShadowEffect(wgt);
    ChangeBKG(wgt,EDIT_WIDGET_BKG);
    wgt->show();
    Resize();
}

bool LoopSegmentWidget::eventFilter(QObject *o, QEvent * e)
{
    if(e->type() == QEvent::HoverMove){
        QHoverEvent* he = static_cast<QHoverEvent*>(e);
        int ex = (int)he->position().x();
        int ey = (int)he->position().y();
        bool flag = false;
        for(int i=0;i<_edit_widgets.size();i++){
            if(_edit_widgets[i]->geometry().contains(ex,ey)){
                int x = _edit_widgets[i]->x()+_edit_widgets[i]->width()-DELBUTTON_WIDTH;
                int y = _edit_widgets[i]->y();
                ActivateRemoveBtn(x,y);
                _del_btn_hovering_wgt = i;
                flag = true;
                break;
            }
        }
        if(flag == false){
            DisabledRemoveBtn();
            _del_btn_hovering_wgt = -1;
        }
    }
    else if(e->type() == QEvent::HoverLeave){
        DisabledRemoveBtn();
        _del_btn_hovering_wgt = -1;
    }
    return QScrollArea::eventFilter(o,e);
}



void LoopSegmentWidget::ActivateRemoveBtn(int x,int y)
{
    _remove_button->setEnabled(true);
    _remove_button->setVisible(true);
    _remove_button->move(x,y);
}

void LoopSegmentWidget::DisabledRemoveBtn()
{
    _remove_button->setEnabled(false);
    _remove_button->setVisible(false);
}

void LoopSegmentWidget::Resize()
{
    int x = EDGE;
    for(int i=0;i<this->_edit_widgets.size();i++){
        _edit_widgets[i]->move(x,0);
        x = _edit_widgets[i]->x()+EDIT_WIDGET_WIDTH + SPACE_BETWEEN_WIDGET;
    }
    _add_button->move(x + (EDIT_WIDGET_WIDTH-ADDBUTTON_WIDTH)/2,(EDIT_WIDGET_HEIGHT-ADDBUTTON_HEIGHT)/2);
    int wid = 2*EDGE + (_edit_widgets.size() + 1) * EDIT_WIDGET_WIDTH + _edit_widgets.size() * SPACE_BETWEEN_WIDGET;
    _inner_widget->resize(wid,EDIT_WIDGET_HEIGHT);
}

void LoopSegmentWidget::RemoveBranch()
{
    if(_del_btn_hovering_wgt!=-1){
        EditWidget* ew = _edit_widgets[_del_btn_hovering_wgt];
        _edit_widgets.erase(_edit_widgets.begin() + _del_btn_hovering_wgt);
        ew->setParent(nullptr);
        delete ew;
        Resize();
    }
}
