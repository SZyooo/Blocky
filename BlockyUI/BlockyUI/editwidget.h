#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include <QWidget>
#include <vector>
#include "commonvalue.h"
class QScrollBar;
class ConditionWidget;
class LegoWidget;
using std::vector;
class BlockWidget;

class EditWidget : public QWidget
{
    Q_OBJECT
public:
    EditWidget();
    void resizeEvent(QResizeEvent *);
    void AddBlock(const BlockWidget& bw, int x, int y);
    void AddBlock(LegoWidget *lw, int x, int y);
    void RemoveBlock(LegoWidget *&bw);
    void MergeBlock(LegoWidget *absorbing, LegoWidget *absorbed, int idx);
    int HoveringBlock(LegoWidget* ground_block,LegoWidget* float_block);
    void SetCondition(QString left,RELATION op,QString right);


    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public slots:
    void HorizontalMove(int val);
    void VerticleMove(int val);
    void IntersectDetect(LegoWidget *lw);
protected:
    void ResetBar();
    void UpdateBlockPosWhenMoveSliderBar(int ox, int oy);
    void UpdateVisibleRect();
    void MoveBlocks(int x, int y,LegoWidget* lw);
private:
    void StopHovering();
    ConditionWidget* _conditionWidget;
    QScrollBar* _vBar,*_hBar;
    QRect _visibleSpace;
    vector<LegoWidget*> _legos;
    enum{BAR_WIDTH = 15};
    int _clider;
    int _chosenBlock;
    enum {LEFT,RIGHT,NONE} _clicked_button;
    QPoint _click_offset;
    int _hovering_block;
};

#endif // EDITWIDGET_H
