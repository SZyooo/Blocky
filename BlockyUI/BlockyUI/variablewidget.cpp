#include "variablewidget.h"
#include <QLabel>
#include <QFontMetrics>
#include <QLineEdit>
VariableWidget::VariableWidget(const VariableWidget &vw)
{
    QString var_name = vw.getVarName();
    _var_name.setParent(this);
    _input.setParent(this);
    _var_name.setText(var_name);
    QFont font;
    font.setPointSize(10);
    QSize size = QFontMetrics(font).boundingRect(var_name).size();
    _var_name.resize(size);
    _var_name.setFont(font);
    _input.setFont(font);
    _input.resize(INPUT_MIN_WIDTH,size.height());
    _var_name.move(EDGE,EDGE);
    _input.move(_var_name.x()+_var_name.width()+SPACING,EDGE);
    resize(_input.x()+_input.width()+EDGE,size.height()+EDGE*2);
    connect(&_input,&QLineEdit::textEdited,this,&VariableWidget::Input);
}

VariableWidget &VariableWidget::operator=(const VariableWidget &vw)
{
    _var_name.setText(vw._var_name.text());
    _input.setText(vw._input.text());
    _var_name.setGeometry(vw._var_name.geometry());
    _input.setGeometry(vw._input.geometry());
    resize(vw.size());
}

VariableWidget::VariableWidget(QString var_name)
{
    _var_name.setParent(this);
    _input.setParent(this);
    _var_name.setText(var_name);
    QFont font;
    font.setPointSize(10);
    QSize size = QFontMetrics(font).boundingRect(var_name).size();
    _var_name.resize(size);
    _var_name.setFont(font);
    _input.setFont(font);
    _input.resize(INPUT_MIN_WIDTH,size.height());
    _var_name.move(EDGE,EDGE);
    _input.move(_var_name.x()+_var_name.width()+SPACING,EDGE);
    resize(_input.x()+_input.width()+EDGE,size.height()+EDGE*2);
    connect(&_input,&QLineEdit::textEdited,this,&VariableWidget::Input);
}

void VariableWidget::SetValue(const QString &val)
{
    _input.setText(val);
}

VariableWidget::~VariableWidget()
{
    _var_name.setParent(nullptr);
    _input.setParent(nullptr);
}

QString VariableWidget::getVarValue() const
{
    return _input.text();
}

QString VariableWidget::getVarName() const
{
    return _var_name.text();
}

void VariableWidget::Input(const QString& s)
{
    int wid = QFontMetrics(_input.font()).boundingRect(s).width();
    if(wid < INPUT_MIN_WIDTH){
        wid = INPUT_MIN_WIDTH;
    }
    _input.resize(wid,_input.height());
    resize(_input.x()+_input.width()+EDGE,_input.height() + 2*EDGE);
}
