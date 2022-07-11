#include "inputwidget.h"
#include <QLineEdit>
#include <QComboBox>
#include <QFont>
#include <QFontMetrics>
#include "tool.h"
#include <QLabel>
InputWidget::InputWidget(const vector<QString> &variable_names)
    :_choises(variable_names),_input(new QLineEdit(this)),_combobox(new QComboBox(this)),
      _input_wid_changed(false),_customized_value(true)
{
    _value = "";

    QFont font;
    font.setPointSize(15);
    _input->setFont(font);
    _combobox->setFont(font);
    _combobox->stackUnder(_input);
    _combobox->addItem("(Type)");

    QString longest_str = "(Type)";
    for(int i=0;i<variable_names.size();i++){
        _combobox->addItem(variable_names[i]);
        if(variable_names[i].length() > longest_str.length())
            longest_str = variable_names[i];
    }

    QSize size = QFontMetrics(font).boundingRect(longest_str).size();
    _dropbox_width = size.width() + DROP_ICON_SIZE;
    _input_width = (int)(_dropbox_width * 0.8f);
    _combobox->resize(_dropbox_width,size.height());
    _input->resize(_input_width,size.height());
    _combobox->move(0,0);
    _input->move(0,0);
    this->resize(_combobox->size());
    connect(_input,&QLineEdit::textChanged,this,&InputWidget::InputValue);
    connect(_input,&QLineEdit::editingFinished,this,&InputWidget::SetValueFinished);
    connect(_combobox,&QComboBox::activated,this,&InputWidget::SelectVariable);
}

void InputWidget::AddVariable(QString variable_name)
{
    _combobox->addItem(variable_name);
}

void InputWidget::RemoveVariable(QString variable_name)
{
    int idx = _combobox->findText(variable_name);
    if(idx!=-1)
    {
         _combobox->removeItem(idx);
    }
}

void InputWidget::InputValue(const QString &s)
{
    int new_width = QFontMetrics(_input->font()).boundingRect(s).width();
    if(new_width > _input_width){
        _input->resize(new_width,_input->height());
        //_input->move(0,0);
        _combobox->resize(new_width+DROP_ICON_SIZE,_combobox->height());
        //_combobox->move(0,0);
        this->resize(_combobox->size());
        emit Resize();
        _input_wid_changed = true;
    }
    else{
        if(_input_wid_changed){
            _input->resize(_input_width,_input->height());
            _combobox->resize(_dropbox_width,_combobox->height());
            _input_wid_changed = false;
            this->resize(_combobox->size());
            emit Resize();
        }
    }
}

void InputWidget::SelectVariable(int idx)
{
    if(idx == 0){
        _input->setEnabled(true);
        _input->setText("");
        _customized_value = true;
    }
    else{
        _input->setText(_combobox->itemText(idx));
        _input->setEnabled(false);
        _customized_value = false;
    }
}

void InputWidget::SetValueFinished()
{
    _value = _input->text();
}
