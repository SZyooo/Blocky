#include "blocklistwidget.h"
#include "tool.h"
#include "blockwidget.h"
#include "innerwidget.h"
BlockListWidget::BlockListWidget(const vector<QString> &OpNames, const vector<QString> &Descriptions, const vector<vector<QString> > &Params, vector<QColor> colors)
{
    int OpCount = OpNames.size();
    int DesCount = Descriptions.size();
    int ParamCount = Params.size();
    int ColorCount = colors.size();
    _innerWidget = new InnerWidget;
    setWidget(_innerWidget);
    for(int i=0;i<OpCount;i++){
        QString des;
        if(i >= DesCount){
            des = "";
        }
        else{
            des = Descriptions[i];
        }
        vector<QString> param;
        if(i < ParamCount){
            param = Params[i];
        }
        QColor color;
        if(i < ColorCount){
            color = colors[i];
        }
        else{
            color = FetchAColor();
        }
        BlockWidget* bw = new BlockWidget(OpNames[i],des,param,color);
        bw->setParent(_innerWidget);
        _blocks.push_back(bw);
    }
    Redraw();
}

void BlockListWidget::resizeEvent(QResizeEvent *)
{
    int wid = width();
    wid = wid > _max_wid?wid : _max_wid;
    int hei = _innerWidget->height();
    _innerWidget->setGeometry(0,0,wid,hei);
}

void BlockListWidget::Redraw()
{
    _max_wid = 0;
    int y = START_Y;
    for(int i=0;i<_blocks.size();i++){
        _blocks[i]->move(ALIGNMENT_X,y);
        TurnOnShadowEffect(_blocks[i]);
        y = _blocks[i]->y() + _blocks[i]->height() + SPACING;
        if(_max_wid < _blocks[i]->width()){
            _max_wid = _blocks[i]->width();
        }
    }
    int wid = _max_wid > width()? _max_wid : width();
    _innerWidget->setGeometry(0,0,wid,y);
}

