#include "editwidget.h"
#include "conditionwidget.h"
#include <QScrollBar>
#include <QRect>
#include <blockwidget.h>
#include <legowidget.h>
#include <QPoint>
#include <QMouseEvent>
#include "tool.h"
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include "blockmimedata.h"
#include <QSize>

EditWidget::EditWidget()
    :_conditionWidget(new ConditionWidget),
      _vBar(new QScrollBar(Qt::Vertical,this)),_hBar(new QScrollBar(Qt::Horizontal,this)),_chosenBlock(-1)
    ,_hovering_block(-1),_placeholder_widget(new QWidget(this))
{
    _conditionWidget->move(0,0);
    _conditionWidget->setParent(this);
    _visibleSpace = QRect(0,0,0,0);
    _vBar->raise();
    _hBar->raise();
    _vBar->setTracking(true);
    _hBar->setTracking(true);
    _conditionWidget->raise();
    _vBar->setMinimum(0);
    _hBar->setMinimum(0);
    connect(_vBar,&QScrollBar::sliderMoved,this,&EditWidget::VerticleMove);
    connect(_hBar,&QScrollBar::sliderMoved,this,&EditWidget::HorizontalMove);
    ResetBar();
    _clider = -1;
    setAcceptDrops(true);
    TurnOnShadowEffect(this);
}

void EditWidget::resizeEvent(QResizeEvent *)
{
    UpdateVisibleRect();
}

void EditWidget::AddBlock(const BlockWidget &bw,int x,int y)
{
    LegoWidget* lw = new LegoWidget(bw);
    AddBlock(lw,x,y);
}

void EditWidget::AddBlock(LegoWidget *lw,int x, int y)
{
    lw->setParent(this);
    lw->setVisible(true);
    lw->move(x,y);
    _conditionWidget->raise();
    _vBar->raise();
    _hBar->raise();
    connect(lw,&LegoWidget::DragMove,this,&EditWidget::IntersectDetect);
    this->_legos.push_back(lw);
}

void EditWidget::RemoveBlock(LegoWidget* &bw)
{
    auto it = _legos.begin();
    while(it!=_legos.end())
    {
        if(*it == bw){
            _legos.erase(it);
            delete bw;
            bw = nullptr;
            break;
        }
    }
}

void EditWidget::MergeBlock(LegoWidget *absorbing, LegoWidget *absorbed,int idx)
{
    absorbing->InsertBlock(idx,absorbed);
    RemoveBlock(absorbed);
}

int EditWidget::HoveringBlock(LegoWidget *ground_block, LegoWidget *float_block)
{
    if(ground_block == float_block)
        return -1;
    int rx = float_block->x() - ground_block->x();
    int ry = float_block->y() - ground_block->y();
    QRect rect(rx,ry,float_block->width(),float_block->height());
    return ground_block->Hovering(rx,ry,rect);
}

void EditWidget::SetCondition(QString left, RELATION op, QString right)
{
    _conditionWidget->SetLeft(left);
    _conditionWidget->SetRight(right);
    _conditionWidget->SetOp(op);
}

void EditWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        _clicked_button = LEFT;
        _chosenBlock = -1;
        for(int i=0;i<_legos.size();i++){
            if(_legos[i]->geometry().contains(event->pos())){
                _chosenBlock = i;
                _click_offset.setX(event->x() - _legos[i]->x());
                _click_offset.setY(event->y() - _legos[i]->y());
                break;
            }
        }
    }
    else if(event->button() == Qt::RightButton){
        _clicked_button = RIGHT;
        for(int i=0;i<_legos.size();i++){
            if(_legos[i]->geometry().contains(event->pos())){
                _click_offset.setX(event->x() - _legos[i]->x());
                _click_offset.setY(event->y() - _legos[i]->y());
                int ox = _legos[i]->x();
                int oy = _legos[i]->y();
                int rx = event->x() - ox;
                int ry = event->y() - oy;
                LegoWidget* splb = _legos[i]->SplitBlock(rx,ry);
                if(splb!=nullptr){
                    AddBlock(splb,ox,oy);
                    _chosenBlock = _legos.size()-1;
                }
                break;
            }
        }
    }
    else{
        _clicked_button = NONE;
        _chosenBlock = -1;
    }
    StopHovering();
    return QWidget::mousePressEvent(event);
}

void EditWidget::mouseMoveEvent(QMouseEvent *event)
{
    switch(_clicked_button){
    case LEFT: case RIGHT:
        if(_chosenBlock!=-1){
            int x = event->x() - _click_offset.x();
            int y = event->y() - _click_offset.y();
            MoveBlocks(x,y,_legos[_chosenBlock]);
        }
        break;
    default:
        break;
    }
    return QWidget::mouseMoveEvent(event);
}

void EditWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(_chosenBlock!=-1){
        IntersectDetect(_legos[_chosenBlock]);
        if(_clider != -1){
            int idx = HoveringBlock(_legos[_clider],_legos[_chosenBlock]);
            if(idx != -1){
                _legos[_clider]->InsertBlock(idx,_legos[_chosenBlock]);
                _legos.erase(_legos.begin()+_chosenBlock);
            }
        }
        else{
            int posX = event->x() - _click_offset.x();
            int posY = event->y() - _click_offset.y();
            _legos[_chosenBlock]->move(posX,posY);
        }
    }
    _clicked_button = NONE;
    _chosenBlock = -1;
    StopHovering();
    return QWidget::mouseReleaseEvent(event);
}

void EditWidget::dragEnterEvent(QDragEnterEvent *event)
{
    const BlockMimeData * blockMimeData = dynamic_cast<const BlockMimeData*>(event->mimeData());
    if(blockMimeData!=nullptr){
        int x = (int)event->position().x();
        int y = (int)event->position().y();
        const BlockWidget* bw = blockMimeData->GetBlock();
        EnablePlaceHolder(x,y,bw->size());
        event->acceptProposedAction();
    }
}

void EditWidget::dragMoveEvent(QDragMoveEvent *event)
{
    const BlockMimeData * blockMimeData = dynamic_cast<const BlockMimeData*>(event->mimeData());
    if(blockMimeData!=nullptr){
        int x = (int)event->position().x();
        int y = (int)event->position().y();
        const BlockWidget* bw = blockMimeData->GetBlock();
        EnablePlaceHolder(x,y,bw->size());
        event->acceptProposedAction();
    }
}

void EditWidget::dragLeaveEvent(QDragLeaveEvent *e)
{
    DisablePlaceHolder();
}

void EditWidget::dropEvent(QDropEvent *event)
{
    const BlockMimeData * blockMimeData = dynamic_cast<const BlockMimeData*>(event->mimeData());
    if(blockMimeData!=nullptr){
        int x = (int)event->position().x();
        int y = (int)event->position().y();
        const BlockWidget* bw = blockMimeData->GetBlock();
        AddBlock(*bw,x,y);
        DisablePlaceHolder();
        event->acceptProposedAction();
    }
}


void EditWidget::HorizontalMove(int val)
{
    int ox = _visibleSpace.x();
    int oy = _visibleSpace.y();
    _visibleSpace.setX(-val);
    UpdateBlockPosWhenMoveSliderBar(ox,oy);
}

void EditWidget::VerticleMove(int val)
{
    int ox = _visibleSpace.x();
    int oy = _visibleSpace.y();
    _visibleSpace.setY(-val);
    UpdateBlockPosWhenMoveSliderBar(ox,oy);
}

void EditWidget::IntersectDetect(LegoWidget *lw)
{
    QRect rect(lw->geometry());
    for(int i=0;i<_legos.size();i++){
        if(_legos[i] == lw)
            continue;
        int lx = _legos[i]->x();
        int ly = _legos[i]->y();
        if(_legos[i]->geometry().contains(rect.x(),rect.y()) || rect.contains(lx,ly)){
            _clider = i;
            return;
        }
    }
    _clider = -1;
}

void EditWidget::ResetBar()
{
    _vBar->setGeometry(width() - BAR_WIDTH,0,BAR_WIDTH,height());
    _hBar->setGeometry(0,height()-BAR_WIDTH,width(),BAR_WIDTH);
    _vBar->setMinimum(0);
    _hBar->setMinimum(0);
    int xRange = _visibleSpace.width()- width();
    int yRange = _visibleSpace.height() - height();
    _vBar->setMaximum(yRange);
    _hBar->setMaximum(xRange);
    _vBar->setValue(-_visibleSpace.y());
    _hBar->setValue(-_visibleSpace.x());
    QString str = QString("xRange = %1,xValue = %2;yRange=%3,yValue=%4")
            .arg(xRange).arg(_hBar->value()).arg(yRange).arg(_vBar->value());
    Debug(str);
    if(_visibleSpace.width() <= width()){
        _hBar->setEnabled(false);
        _hBar->setVisible(false);
    }
    else{
        _hBar->setEnabled(true);
        _hBar->setVisible(true);

    }
    if(_visibleSpace.height() <= height()){
        _vBar->setEnabled(false);
        _vBar->setVisible(false);
    }
    else{
        _vBar->setEnabled(true);
        _vBar->setVisible(true);
    }
}

void EditWidget::UpdateBlockPosWhenMoveSliderBar(int ox,int oy)
{
    for(int i=0;i<_legos.size();i++){
        int dx = _legos[i]->x() - ox;
        int dy = _legos[i]->y() - oy;
        _legos[i]->move(_visibleSpace.x() + dx,_visibleSpace.y() + dy);
    }
}

void EditWidget::MoveBlocks(int x, int y,LegoWidget* lw)
{
    lw->move(x,y);
    IntersectDetect(lw);
    if(_clider!=-1){
        _hovering_block = _clider;
        HoveringBlock(_legos[_clider],lw);
    }
    else{
        StopHovering();
    }
    UpdateVisibleRect();
}

void EditWidget::DisablePlaceHolder()
{
    _placeholder_widget->close();
}

void EditWidget::EnablePlaceHolder(int x,int y, QSize size)
{
    _placeholder_widget->show();
    ChangeBKG(_placeholder_widget,Qt::gray);
    _placeholder_widget->setGeometry(x,y,size.width(),size.height());
}

void EditWidget::StopHovering()
{
    if(_hovering_block!=-1){
        _legos[_hovering_block]->StopHovering();
    }
    _hovering_block = -1;
}

void EditWidget::UpdateVisibleRect()
{
    int minX=0,minY=0,maxX=width(),maxY=height();
    for(int i = 0;i<this->_legos.size();i++){
        int lx = _legos[i]->x();
        int uy = _legos[i]->y();
        int rx = lx + _legos[i]->width();
        int by = uy + _legos[i]->height();
        if(minX > lx){
            minX = lx;
        }
        if(maxX < rx){
            maxX = rx;
        }
        if(minY > uy){
            minY = uy;
        }
        if(maxY < by){
            maxY = by;
        }
    }
    _visibleSpace.setX(minX);
    _visibleSpace.setY(minY);
    _visibleSpace.setWidth(maxX - minX);
    _visibleSpace.setHeight(maxY - minY);
    QString msg = QString("Rect = [(%1,%2),(%3,%4)]").arg(minX).arg(minY).arg(maxX).arg(maxY);
    Debug(msg);
    ResetBar();
}
