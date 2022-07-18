#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QMainWindow>
#include <QWidget>
class BlockBox;
class SegmentContainerWidget;
class VariableList;
class QHBoxLayout;
class EditWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditWindow();
private:
    QWidget* _widget;
    enum{BLOCKBOX = 2,SEGMENT_CONTAINER=6,VARIABLE_LIST = 2};
    BlockBox* _kit_blocks;
    SegmentContainerWidget* _segments;
    VariableList* _variables;
    QHBoxLayout *_layout;
};
#endif // EDITWINDOW_H
