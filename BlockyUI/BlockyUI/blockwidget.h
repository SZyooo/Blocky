#ifndef BLOCKWIDGET_H
#define BLOCKWIDGET_H

#include <QWidget>
#include <vector>

class QLabel;
class InputWidget;

using std::vector;
using std::pair;

enum class AREA{IN_LIST,IN_EDITOR};
class BlockWidget : public QWidget
{
    Q_OBJECT
public:
    BlockWidget(QString op,QString des,const vector<QString>& params,AREA area = AREA::IN_LIST);
    void paintEvent(QPaintEvent *event);
private:
    QLabel* _operation_label;
    QString _op_name;
    QString _toolTip;
    vector<pair<QLabel*,InputWidget*>> _params;
    enum{FONTSIZE = 10,EDGE = 5,SPACE = 6};
    AREA _area;
    int mid;
};

#endif // BLOCKWIDGET_H
