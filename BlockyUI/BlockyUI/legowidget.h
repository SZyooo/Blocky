#ifndef LEGOWIDGET_H
#define LEGOWIDGET_H

#include <QWidget>
#include <vector>
#include <QRect>
#include "lbwidget.h"

class BlockWidget;
class LegoWidget : public QWidget
{
    Q_OBJECT
public:
    //add a copy of bw
    LegoWidget(const BlockWidget &pbw);
    QColor GetColor();
    //add lw to self directly
    void InsertBlock(int idx,LegoWidget* lw);
    //return proper idx or -1
    int Hovering(int rx,int ry,const QRect& rect);
    void StopHovering();
    void RemoveBlock(LegoWidget *&lw);
    void RemoveBlock(int idx);
    void ReDraw();
    void moveEvent(QMoveEvent *event);
    void ChangeColor(QColor color);
    LegoWidget* SplitBlock(int rx, int ry);
    int GetProperInsertIdx(QPoint p);
protected:
    void HoveringDraw(int idx,QRect rect);
signals:
    void Resize();
    void DragMove(LegoWidget* l);
private:
    void DisablePlaceholder();
    void ActivatePlaceholder();
    LegoWidget(){}
    std::vector<LegoWidget*> _blocks;
    QColor _color;
    QWidget _placeholder;
};

#endif // LEGOWIDGET_H
