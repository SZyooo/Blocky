#include "blockbox.h"
#include "blocklistwidget.h"

BlockBox::BlockBox()
{

}

void BlockBox::AddKit(const QString &kit_name, const vector<QString> &OpNames, const vector<QString> &Descriptions, const vector<vector<QString> > &Params, vector<QColor> colors)
{
    if(_kits.find(kit_name)!=_kits.end()){
        throw "existed kit!";
    }
    BlockListWidget* blw = new BlockListWidget(OpNames,Descriptions,Params,colors);
    int idx = addItem(blw,kit_name);
    pair<BlockListWidget*,int> p(blw,idx);
    pair<QString,pair<BlockListWidget*,int>> p2(kit_name,p);
    _kits.insert(p2);
}

void BlockBox::RemoveKit(const QString &kit_name)
{
    if(_kits.find(kit_name) ==_kits.end()){
        throw "no such kit!";
    }
    int idx = _kits[kit_name].second;
    QWidget* w = widget(idx);
    removeItem(idx);
    delete w;
}
