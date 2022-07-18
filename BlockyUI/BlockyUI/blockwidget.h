#ifndef BLOCKWIDGET_H
#define BLOCKWIDGET_H

#include <QWidget>
#include <vector>

class QLabel;
class InputWidget;

using std::vector;
using std::pair;

QColor FetchAColor();


class BlockWidget : public QWidget
{
    Q_OBJECT
public:
    BlockWidget(QString op,QString des,const vector<QString>& params,QColor color = FetchAColor());
    BlockWidget(const BlockWidget& bw);
    void paintEvent(QPaintEvent *event);
    QColor GetBackgoundColor() const;

    void SetAcceptDrag(bool _draggable);

    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent* e);

public slots:
    void Resize();
    void SelectVar();
    void InputVal(const QString&s);

private:
    QLabel* _operation_label;
    QString _op_name;
    QString _toolTip;
    vector<pair<QLabel*,InputWidget*>> _params;
    vector<QString> _params_str;
    vector<bool> _is_var;
    vector<QString> _values;
    enum{FONTSIZE = 10,EDGE = 5,SPACE = 6};
    int mid;
    QColor _color;

    QPoint _press_pos;
    bool _pressed;
    bool _accept_drag;
    enum{DRAG_THRESHOLD = 6};
};

#endif // BLOCKWIDGET_H
