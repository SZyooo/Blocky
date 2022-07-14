#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>
#include <vector>

class QLineEdit;
class QComboBox;
class QLabel;
using std::vector;
class InputWidget : public QWidget
{
    Q_OBJECT
public:

    explicit InputWidget();
    static void AddVariable(QString variable_name);
    static void RemoveVariable(QString variable_name);
    bool IsCustomizedValue(){return _customized_value;}
    QString FetchValue() {return _value;}
    void UpdateComboBox();
    void UpdateSize();
    void SetValue(QString s);
public slots:
    void InputValue(const QString& s);
    void SelectVariable(int idx);
    void SetValueFinished();

signals:
    void Resize();
    void ChooseVar(QString& var);
    void InputVal(QString& val);
private:
    QLineEdit* _input;
    QComboBox* _combobox;
    QString _value;
    bool _customized_value;
    enum{DROP_ICON_SIZE = 20};

    static vector<QString> Choices;
};

#endif // INPUTWIDGET_H
