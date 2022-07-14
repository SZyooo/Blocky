#ifndef CONDITIONWIDGET_H
#define CONDITIONWIDGET_H

#include <QWidget>
#include <QString>
#include <vector>
#include "commonvalue.h"
class InputWidget;
class QComboBox;

class ConditionWidget : public QWidget
{
    Q_OBJECT
public:
    ConditionWidget();
    QString LeftValue();
    void SetLeft(QString s);
    QString RightValue();
    void SetOp(RELATION r);
    void SetRight(QString s);
    QString Operator();
public slots:
    void SelectLeftVar();
    void TypeLeftVal(QString& val);
    void SelectRightVar();
    void TypeRightVal(QString& val);
    void Resize();
    void SelectOp(int idx);

private:
    enum{FONT_SIZE = 10,EDGE = 5,SPACE = 6};
    InputWidget* _left,*_right;
    QComboBox* _op;
    const static std::vector<QString> OPERATORS;
    int _height;

    QString _left_val,_right_val,_op_type;
    bool _left_is_var,_right_is_var;

};

#endif // CONDITIONWIDGET_H
