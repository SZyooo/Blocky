#ifndef LOOPSEGMENTWIDGET_H
#define LOOPSEGMENTWIDGET_H

#include <QScrollArea>
#include<vector>
using std::vector;
class EditWidget;
class QPushButton;
class InnerWidget;
class LoopSegmentWidget : public QScrollArea
{
    Q_OBJECT
public:
    LoopSegmentWidget();
    void resizeEvent(QResizeEvent *);
    void AddBranch();
    bool eventFilter(QObject *, QEvent *e);
    enum{EDIT_WIDGET_HEIGHT = 600,EDIT_WIDGET_WIDTH = 400};
    enum{ADDBUTTON_WIDTH = 100,ADDBUTTON_HEIGHT = 70};
    enum{DELBUTTON_WIDTH = 30,DELBUTTON_HEIGHT=30};
    enum{SPACE_BETWEEN_WIDGET = 8,EDGE = 5};
signals:
private:
    void ActivateRemoveBtn(int x, int y);
    void DisabledRemoveBtn();
    void Resize();
    InnerWidget* _inner_widget;
    vector<EditWidget*> _edit_widgets;
    QPushButton* _add_button;
    QPushButton* _remove_button;
    void RemoveBranch();
    int _del_btn_hovering_wgt;
};

#endif // LOOPSEGMENTWIDGET_H
