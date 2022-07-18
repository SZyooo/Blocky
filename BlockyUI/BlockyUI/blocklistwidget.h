#ifndef BLOCKLISTWIDGET_H
#define BLOCKLISTWIDGET_H

#include <QScrollArea>
#include <vector>
using std::vector;

class BlockWidget;
class InnerWidget;
class BlockListWidget : public QScrollArea
{
    Q_OBJECT
public:
    BlockListWidget(const vector<QString>& OpNames, const vector<QString>& Descriptions,
                    const vector<vector<QString>>& Params, vector<QColor> colors);
    void resizeEvent(QResizeEvent *);
private:
    void Redraw();
    InnerWidget* _innerWidget;
    vector<BlockWidget*> _blocks;
    enum{ALIGNMENT_X = 10,START_Y,SPACING = 8};
    int _max_wid;
};

#endif // BLOCKLISTWIDGET_H
