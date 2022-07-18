#ifndef VARIABLEWIDGET_H
#define VARIABLEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>


class VariableWidget : public QWidget
{
    Q_OBJECT
public:
    VariableWidget(const VariableWidget& vw);
    VariableWidget& operator=(const VariableWidget& vw);
    VariableWidget(QString var_name);
    void SetValue(const QString& val);
    ~VariableWidget();
    QString getVarValue() const;
    QString getVarName() const;
signals:
public slots:
    void Input(const QString &s);
private:
    QLabel _var_name;
    QLineEdit _input;
    enum{SPACING = 6,EDGE = 5,INPUT_MIN_WIDTH = 40};
};

#endif // VARIABLEWIDGET_H
