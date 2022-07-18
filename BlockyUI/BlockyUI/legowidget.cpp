#include "legowidget.h"
#include "tool.h"
#include <QMoveEvent>
#include <blockwidget.h>
LegoWidget::LegoWidget(const BlockWidget& pbw)
    :_color(pbw.GetBackgoundColor()),_placeholder(this)
{
    LegoWidget* lw = new LegoWidget;
    BlockWidget *bw = new BlockWidget(pbw);
    bw->SetAcceptDrag(false);
    bw->setParent(lw);
    bw->move(0,0);
    lw->resize(bw->size());
    _blocks.push_back(lw);
    lw->setParent(this);
    lw->move(0,0);
    resize(lw->size());
    lw->move(0,0);
    ChangeBKG(&_placeholder,Qt::gray);
    DisablePlaceholder();

}

QColor LegoWidget::GetColor()
{
    return _color;
}

void LegoWidget::InsertBlock(int idx, LegoWidget *lw)
{
    if(idx < 0 || idx > _blocks.size())
        return;
    lw->setParent(this);
    lw->show();
    lw->ChangeColor(_color);
    _blocks.insert(_blocks.begin()+idx,lw);
    ReDraw();
}

int LegoWidget::Hovering(int rx, int ry, const QRect &rect)
{
    int idx = -1;
    if(rx > width() || rx < 0)
        return -1;
    if(ry < 0 || ry > height())
        return -1;
    int y = 0;
    for(int i=0;i<_blocks.size();i++){
        int w = _blocks[i]->height() / 2;
        if(abs(ry - y) <= w)
        {
            idx = i;
            HoveringDraw(idx,rect);
            return idx;
        }
        else y += _blocks[i]->height();
    }
    idx = _blocks.size();
    HoveringDraw(idx,rect);
    return idx;
}

void LegoWidget::StopHovering()
{
    DisablePlaceholder();
    ReDraw();
}

void LegoWidget::RemoveBlock(LegoWidget* &lw)
{
    for(int i=0;i<_blocks.size();i++){
        if(_blocks[i] == lw){
            _blocks.erase(_blocks.begin() + i);
            if(width() == lw->x() + lw->width() || height() == lw->y() + lw->height()){
                int w = 0,h = 0;;
                for(int i=0;i<_blocks.size();i++){
                    if(w < _blocks[i]->x() + _blocks[i]->width()){
                        w = _blocks[i]->width() + _blocks[i]->x();
                    }
                    if(h < _blocks[i]->height() + _blocks[i]->y()){
                        h = _blocks[i]->height() + _blocks[i]->y();
                    }
                }
                ReDraw();
            }
            delete lw;
            lw = nullptr;
            return;
        }
    }
}

void LegoWidget::RemoveBlock(int idx)
{
    if(idx < 0 || idx >= _blocks.size())
        return;
    LegoWidget* removedLw = _blocks[idx];
    RemoveBlock(removedLw);
}

void LegoWidget::ReDraw()
{
    int w = 0;
    int y = 0;
    for(int i=0;i<_blocks.size();i++){
        _blocks[i]->move(0,y);
        y =_blocks[i]->height() + _blocks[i]->y();
        if(w < _blocks[i]->width())
            w = _blocks[i]->width();
    }
    this->resize(w,y);
}

void LegoWidget::moveEvent(QMoveEvent *event)
{
    emit DragMove(this);
    return QWidget::moveEvent(event);
}

void LegoWidget::ChangeColor(QColor color)
{
    for(int i=0;i<_blocks.size();i++){
        BlockWidget* bw = static_cast<BlockWidget*>(_blocks[i]->children()[0]);
        ChangeBKG(bw,color);
    }
}

LegoWidget *LegoWidget::SplitBlock(int rx, int ry)
{
    for(int i = 0;i<this->_blocks.size();i++){
        if(_blocks[i]->geometry().contains(rx,ry))
        {
            LegoWidget* split_widget = _blocks[i];
            split_widget->setParent(nullptr);
            split_widget->ChangeColor(FetchAColor());
            _blocks.erase(_blocks.begin() + i);
            return split_widget;
        }
    }
    return nullptr;
}

int LegoWidget::GetProperInsertIdx(QPoint p)
{
    int x = p.x();
    if(x < 0 || x > width())
        return -1;
    int y = p.y();
    int cur_y = 0;
    for(int i=0;i<_blocks.size();i++){
        int w = _blocks[i]->height() / 2;
        if(abs(y - cur_y) <= w)
        {
            return i;
        }
        else cur_y += _blocks[i]->height();
    }
}

void LegoWidget::HoveringDraw(int idx, QRect rect)
{
    if(idx == -1 || idx > _blocks.size())
        return;
    int w = rect.width() > width()?rect.width():width();
    int h = height() + rect.height();
    resize(w,h);
    if(idx != _blocks.size()){
        int cur_y = 0;
        bool drawn = false;
        for(int i=0;i<_blocks.size();i++){
            if(i == idx && drawn == false){
                ActivatePlaceholder();
                _placeholder.resize(rect.size());
                _placeholder.move(0,cur_y);
                cur_y = _placeholder.y() + _placeholder.height();
                drawn = true;
                i --;
            }
            else{
               _blocks[i]->move(0,cur_y);
               cur_y = _blocks[i]->y() + _blocks[i]->height();
            }
        }
    }
    else{
        ActivatePlaceholder();
        _placeholder.resize(rect.size());
        _placeholder.move(0,y() + height());
    }
    //TurnOnShadowEffect(this);
}

void LegoWidget::DisablePlaceholder()
{
    _placeholder.setVisible(false);
    _placeholder.setEnabled(false);
}

void LegoWidget::ActivatePlaceholder()
{
    _placeholder.setVisible(true);
    _placeholder.setEnabled(true);
}
