#ifndef BLOCKBOX_H
#define BLOCKBOX_H

#include <QToolBox>
#include <vector>
class BlockListWidget;
using std::pair;
using std::unordered_map;
using std::vector;
class BlockBox : public QToolBox
{
    Q_OBJECT
public:
    BlockBox();
    void AddKit(const QString& kit_name,const vector<QString>& OpNames, const vector<QString>& Descriptions,
                const vector<vector<QString>>& Params, vector<QColor> colors);
    void RemoveKit(const QString& kit_name);
private:
    unordered_map<QString,pair<BlockListWidget*,int>> _kits;
};

#endif // BLOCKBOX_H
