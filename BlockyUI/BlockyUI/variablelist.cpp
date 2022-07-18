#include "variablelist.h"
#include <QEvent>
#include <QResizeEvent>
#include <QDialog>
#include <QMessageBox>
#include "tool.h"
#include "commonvalue.h"
VariableList::VariableList()
{
    setWidget(&_inner_widget);
    _add_btn.setParent(&_inner_widget);
    _add_btn.setText("ADD");
    QFont font;
    font.setPointSize(8);
    _add_btn.resize(ADD_BUTTON_WIDTH,ADD_BUTTON_HEIGHT);
    _del_btn.setParent(&_inner_widget);
    _add_btn.setFont(font);
    _del_btn.resize(DEL_BUTTON_WIDTH,DEL_BUTTON_HEIGHT);
    _del_btn.setText("X");
    _del_btn.setFont(font);
    _max_width = EDGE + _add_btn.width() + EDGE;
    Redraw();
    setAttribute(Qt::WA_Hover,true);
    _del_idx = -1;
    connect(&_add_btn,&QPushButton::clicked,this,&VariableList::ShowDialog);
    connect(&_add_dialog,&AddVariableDialog::Close,this,&VariableList::WhenDialogClosed);
    connect(&_del_btn,&QPushButton::clicked,this,&VariableList::RemoveVariable);
}

VariableList::~VariableList()
{
    _add_btn.setParent(nullptr);
    _del_btn.setParent(nullptr);
    for(int i=0;i<_variables.size();i++){
        _variables[i].setParent(nullptr);
    }
    _add_dialog.setParent(nullptr);
}

void VariableList::Redraw()
{
    int y = EDGE;
    int max_w = 0;
    for(int i=0;i<_variables.size();i++){
        _variables[i].setParent(&_inner_widget);
        ChangeBKG(&_variables[i],VARIABLE_COLOR);
        TurnOnShadowEffect(&_variables[i]);
        AddRadius(&_variables[i],15);
        _variables[i].move(ALIGN_X,y);
        _variables[i].show();
        y+=_variables[i].height() + SPACING;
        if(max_w < _variables[i].width()){
            max_w = _variables[i].width();
        }
    }
    _add_btn.move(ALIGN_X,y);
    max_w = max_w+EDGE*2;
    if(max_w > _max_width){
        _max_width = max_w;
    }
    if(max_w < width()){
        max_w = width();
    }
    _inner_widget.resize(max_w,y+_add_btn.height() + EDGE);
    DisableDelButton();
}

bool VariableList::event(QEvent *e)
{
    if(e->type() == QEvent::HoverMove){
        QPoint p = _inner_widget.MousePos();
        int idx = GetVariableIndexByMousePos(p.x(),p.y());
        if(idx != -1){
            EnableDelButtonAt(idx);
        }
        else{
            DisableDelButton();
        }
    }
    return QScrollArea::event(e);
}

void VariableList::resizeEvent(QResizeEvent *e)
{
    int w = e->size().width()>_max_width?e->size().width():_max_width;
    _inner_widget.resize(w,_inner_widget.height());
}

void VariableList::AddVariable(QString var,QString val = "")
{
    _variables.push_back(VariableWidget(var));
    int idx = _variables.size() - 1;
    _variables[idx].SetValue(val);
    Redraw();
}

void VariableList::RemoveVariable()
{
    if(_del_idx!=-1){
        _variables.erase(_variables.begin() + _del_idx);
    }
    Redraw();
}

void VariableList::DisableDelButton()
{
    _del_btn.setEnabled(false);
    _del_btn.setVisible(false);
}

void VariableList::EnableDelButtonAt(int idx)
{
    if(idx < 0 || idx > _variables.size())
        return;
    _del_idx = idx;
    int x = _variables[idx].x() + _variables[idx].width() - DEL_BUTTON_WIDTH;
    int y = _variables[idx].y();
    _del_btn.move(x,y);
    _del_btn.setEnabled(true);
    _del_btn.setVisible(true);
    _del_btn.raise();
}

int VariableList::GetVariableIndexByMousePos(int x, int y)
{
    int idx = -1;
    for(int i=0;i<_variables.size();i++){
        if(_variables[i].geometry().contains(x,y)){
            idx = i;
            break;
        }
    }
    return idx;
}

void VariableList::ShowDialog()
{
    _add_dialog.exec();
}

void VariableList::WhenDialogClosed()
{
    if(_add_dialog.GetCode() == QDialog::Accepted){
        QString var_name = _add_dialog.GetName();
        QString var_value = _add_dialog.GetValue();
        QString msg;
        if(CheckVar(var_name,msg)){
            AddVariable(var_name,var_value);
        }
        else{
            QMessageBox::warning(this,"Invilid Variable Name",msg,QMessageBox::Ok);
        }
    }
}

bool VariableList::CheckVar(const QString& var,QString& out_msg)
{
    //need to finish
    return true;
}

