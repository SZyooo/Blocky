#ifndef VARIABLELIST_H
#define VARIABLELIST_H

#include <QScrollArea>
#include "variablewidget.h"
#include <vector>
#include <QPushButton>
#include "innerwidget.h"
#include "addvariabledialog.h"
using std::vector;
class VariableList : public QScrollArea
{
    Q_OBJECT
public:
    VariableList();
    ~VariableList();
    void Redraw();
    bool event(QEvent *e);
    void resizeEvent(QResizeEvent *e);
    void AddVariable(QString var, QString val);
    void RemoveVariable();
private:
    void DisableDelButton();
    void EnableDelButtonAt(int idx);
    int GetVariableIndexByMousePos(int x,int y);
    void ShowDialog();
    void WhenDialogClosed();
    bool CheckVar(const QString &var, QString &out_msg);
    vector<VariableWidget> _variables;
    QPushButton _add_btn;
    QPushButton _del_btn;
    InnerWidget _inner_widget;
    enum{DEL_BUTTON_WIDTH = 20,DEL_BUTTON_HEIGHT = 20};
    enum{ADD_BUTTON_WIDTH = 30,ADD_BUTTON_HEIGHT = 30};
    enum{SPACING = 3,EDGE = 6,ALIGN_X = 5};
    int _max_width;
    int _del_idx;
    AddVariableDialog _add_dialog;
};

#endif // VARIABLELIST_H
