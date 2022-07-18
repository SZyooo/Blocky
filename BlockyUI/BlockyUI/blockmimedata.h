#ifndef BLOCKMIMEDATA_H
#define BLOCKMIMEDATA_H

#include <QMimeData>
#include <vector>
using std::vector;
#include <QColor>
QColor FetchAColor();
class BlockWidget;
class BlockMimeData : public QMimeData
{
    Q_OBJECT
public:
    BlockMimeData(QString op,QString des,const vector<QString>& params,QColor color = FetchAColor());
    const BlockWidget *GetBlock() const;
    ~BlockMimeData();
private:
    BlockWidget* _block;
};

#endif // BLOCKMIMEDATA_H
