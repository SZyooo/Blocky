#include "editwindow.h"
#include <blockbox.h>
#include <segmentcontainerwidget.h>
#include <variablelist.h>
#include <QHBoxLayout>
#include <vector>
using std::vector;
EditWindow::EditWindow()
    :_widget(new QWidget),_kit_blocks(new BlockBox),
      _segments(new SegmentContainerWidget),_variables(new VariableList),
      _layout(new QHBoxLayout)
{
    vector<QString> ops = {"add","sub"};
    vector<QString> des = {"addition","substraction"};
    vector<QString> param1{"p1","p2"};
    vector<QString> param2{"p1","p2"};
    vector<vector<QString>> params{param1,param2};
    _kit_blocks->AddKit("Basic Kit",ops,des,params,{});
    setCentralWidget(_widget);
    _widget->setLayout(_layout);
    _layout->addWidget(_kit_blocks,BLOCKBOX);
    _layout->addWidget(_segments,SEGMENT_CONTAINER);
    _layout->addWidget(_variables,VARIABLE_LIST);
}
