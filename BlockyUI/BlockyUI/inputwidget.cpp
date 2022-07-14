#include "inputwidget.h"
#include <QLineEdit>
#include <QComboBox>
#include <QFont>
#include <QFontMetrics>
#include "tool.h"
#include <QLabel>
InputWidget::InputWidget()
    :_input(new QLineEdit(this)),_combobox(new QComboBox(this)),
      _customized_value(true)
{
    _value = "";

    QFont font;
    font.setPointSize(15);
    _input->setFont(font);
    _combobox->setFont(font);
    _combobox->stackUnder(_input);
    _combobox->addItem("(Type)");
    _combobox->addItem("(Refresh)");

    for(int i=0;i<InputWidget::Choices.size();i++){
        _combobox->addItem(InputWidget::Choices[i]);
    }

    UpdateSize();

    connect(_input,&QLineEdit::textChanged,this,&InputWidget::InputValue);
    connect(_input,&QLineEdit::editingFinished,this,&InputWidget::SetValueFinished);
    connect(_combobox,&QComboBox::activated,this,&InputWidget::SelectVariable);
}

void InputWidget::AddVariable(QString variable_name)
{
    InputWidget::Choices.push_back(variable_name);
}

void InputWidget::RemoveVariable(QString variable_name)
{
    auto it = InputWidget::Choices.begin();
    while(*it!=variable_name)
        it++;
    if(it!=InputWidget::Choices.end()){
        InputWidget::Choices.erase(it);
    }
}

void InputWidget::UpdateComboBox()
{
    _combobox->clear();
    _combobox->addItem("(Type)");
    _combobox->addItem("(Refresh)");
    for(int i=0;i<InputWidget::Choices.size();i++){
        _combobox->addItem(InputWidget::Choices[i]);
    }
    UpdateSize();
}

void InputWidget::UpdateSize()
{
    QString longest_str = "(Refresh)";
    for(int i=0;i<InputWidget::Choices.size();i++){
        if(InputWidget::Choices[i].length() > longest_str.length())
            longest_str = InputWidget::Choices[i];
    }
    QFont font;
    font.setPointSize(15);
    QSize size = QFontMetrics(font).boundingRect(longest_str).size();
    int _dropbox_width = size.width() + DROP_ICON_SIZE;
    int _input_width = size.width();
    _combobox->resize(_dropbox_width,size.height());
    _input->resize(_input_width,size.height());
    _combobox->move(0,0);
    _input->move(0,0);
    this->resize(_combobox->size());
}

void InputWidget::SetValue(QString s)
{
    _input->setText(s);
}

void InputWidget::InputValue(const QString &s)
{
    int new_width = QFontMetrics(_input->font()).boundingRect(s).width();
    if(new_width > _input->width()){
        _input->resize(new_width,_input->height());
        _combobox->resize(new_width+DROP_ICON_SIZE,_combobox->height());
        this->resize(_combobox->size());
        emit Resize();
    }
}

void InputWidget::SelectVariable(int idx)
{
    if(idx == 0){
        _input->setEnabled(true);
        _input->setText("");
        _customized_value = true;
    }
    else if(idx == 1){
        UpdateComboBox();
    }
    else{
        _input->setText(_combobox->itemText(idx));
        _input->setEnabled(false);
        _customized_value = false;
        QString txt = _combobox->itemText(idx);
        emit ChooseVar(txt);
    }
}

void InputWidget::SetValueFinished()
{
    _value = _input->text();
    QString txt = _input->text();
    emit InputVal(txt);
}


std::vector<QString> InputWidget::Choices;
