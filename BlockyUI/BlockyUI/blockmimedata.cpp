#include "blockmimedata.h"
#include "tool.h"
#include "blockwidget.h"


BlockMimeData::BlockMimeData(QString op, QString des, const vector<QString> &params, QColor color)
{
    _block = new BlockWidget(op,des,params,color);
}


const BlockWidget *BlockMimeData::GetBlock() const
{
    return _block;
}

BlockMimeData::~BlockMimeData()
{
    delete _block;
    _block = nullptr;
}

