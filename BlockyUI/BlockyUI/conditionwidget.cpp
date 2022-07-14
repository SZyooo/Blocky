#include "conditionwidget.h"
#include <inputwidget.h>
#include <QComboBox>
#include <QFont>
#include <QFontMetrics>
#include <cmath>
ConditionWidget::ConditionWidget()
    :_left(new InputWidget),_right(new InputWidget),_op(new QComboBox)
{
    _left->setParent(this);
    _right->setParent(this);
    _op->setParent(this);
    QString str = "";
    for(int i=0;i<ConditionWidget::OPERATORS.size();i++){
        _op->addItem(ConditionWidget::OPERATORS[i]);
        if(ConditionWidget::OPERATORS[i].length() > str.length())
            str = ConditionWidget::OPERATORS[i];
    }
    _op->setCurrentIndex(0);

    QFont font;
    font.setPointSize(FONT_SIZE);
    _op->setFont(font);
    QFontMetrics fm(font);
    QSize size = fm.boundingRect(str).size();
    _op->resize(size.width()+fm.averageCharWidth()*4,size.height());
    _height = std::max(std::max(_left->height(),_right->height()),size.height()) + EDGE *2;

    Resize();

    connect(_left,&InputWidget::ChooseVar,this,&ConditionWidget::SelectLeftVar);
    connect(_left,&InputWidget::InputVal,this,&ConditionWidget::TypeLeftVal);
    connect(_right,&InputWidget::ChooseVar,this,&ConditionWidget::SelectRightVar);
    connect(_right,&InputWidget::InputVal,this,&ConditionWidget::TypeRightVal);
    connect(_left,&InputWidget::Resize,this,&ConditionWidget::Resize);
    connect(_right,&InputWidget::Resize,this,&ConditionWidget::Resize);
    connect(_op,&QComboBox::activated,this,&ConditionWidget::SelectOp);

    _left_is_var = _right_is_var = false;
    _left_val = _right_val = "";
}

void ConditionWidget::SelectLeftVar()
{
    _left_is_var = true;
    _left_val = _left->FetchValue();
}

void ConditionWidget::TypeLeftVal(QString &val)
{
    _left_is_var = false;
    _left_val = val;
}

void ConditionWidget::SelectRightVar()
{
    _right_is_var = true;
    _right_val = _right->FetchValue();
}

void ConditionWidget::TypeRightVal(QString &val)
{
    _right_is_var = false;
    _right_val = val;
}

void ConditionWidget::Resize()
{
    _left->move(EDGE,(_height - _left->height())/2);
    _op->move(_left->x() + _left->width()+SPACE,(_height - _op->height())/2);
    _right->move(_op->x() + _op->width()+SPACE,(_height - _right->height())/2);
    this->resize(SPACE*2+EDGE*2+_left->width()+_op->width()+_right->width(),_height);
}

void ConditionWidget::SelectOp(int idx)
{
    _op_type = ConditionWidget::OPERATORS[idx];
}

QString ConditionWidget::LeftValue()
{
    return _left_val;
}

void ConditionWidget::SetLeft(QString s)
{
    _left_val = s;
    _left->SetValue(s);
}

QString ConditionWidget::RightValue()
{
    return _right_val;
}

void ConditionWidget::SetOp(RELATION r)
{
    _op_type = ConditionWidget::OPERATORS[r];
    _op->setCurrentIndex(r);
}

void ConditionWidget::SetRight(QString s)
{
    _right_val = s;
    _right->SetValue(s);
}

QString ConditionWidget::Operator()
{
    return _op_type;
}

const std::vector<QString> ConditionWidget::OPERATORS  = {"<",">","<=",">=","=","!="};
