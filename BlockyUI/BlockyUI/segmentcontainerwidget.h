#ifndef SEGMENTCONTAINERWIDGET_H
#define SEGMENTCONTAINERWIDGET_H

#include <QScrollArea>
#include <vector>
#include <QPushButton>
using std::vector;

class LoopSegmentWidget;
class SegmentContainerWidget : public QScrollArea
{
    Q_OBJECT
public:
    SegmentContainerWidget();
    ~SegmentContainerWidget();
    void AddSegment();
    void RemoveSegment();
    void Redraw();
    void resizeEvent(QResizeEvent *e);
    bool eventFilter(QObject *, QEvent *e);
private:
    vector<LoopSegmentWidget*> _segments;
    QPushButton _add_button;
    enum{ADDBUTTON_WIDTH = 80,ADDBUTTON_HEIGHT = 80};
    QPushButton _del_button;
    enum{DELBUTTON_WIDTH = 40,DELBUTTON_HEIGHT = 40};
    QWidget _inner_widget;
    enum{EDGE = 5,SPACING = 6};
    void ShowDelButtonAt(int idx);
    int GetSegmentIndexByMouseLocalPos(int x,int y);
    void DisableDelButton();
    void EnableDelButton();
    int _delBtn_hovering;
};

#endif // SEGMENTCONTAINERWIDGET_H
