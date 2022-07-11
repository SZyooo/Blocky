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

    explicit InputWidget(const vector<QString>& variable_names);
    void AddVariable(QString variable_name);
    void RemoveVariable(QString variable_name);
    bool IsCustomizedValue(){return _customized_value;}
    QString FetchValue() {return _value;}
public slots:
    void InputValue(const QString& s);
    void SelectVariable(int idx);
    void SetValueFinished();
signals:
    void Resize();
private:
    vector<QString> _choises;
    QLineEdit* _input;
    QComboBox* _combobox;
    QString _value;
    int _input_width;
    int _dropbox_width;
    int _dropbox_x;

    bool _input_wid_changed;
    bool _customized_value;
    enum{DROP_ICON_SIZE = 20};

};

#endif // INPUTWIDGET_H
