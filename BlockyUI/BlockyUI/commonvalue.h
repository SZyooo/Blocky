#ifndef COMMONVALUE_H
#define COMMONVALUE_H

#include<vector>

class QColor;
extern QColor BLOCK_COLOR;
extern QColor EDIT_WIDGET_BKG;
extern QColor SEGMENT_BKG;
using std::vector;
extern vector<QColor> RandomColors;
enum RELATION{LESSTHAN = 0,GREATERTHAN,LESSEQUAL,GREATEREQUAL,EQUAL,NOTEQUAL};
#endif // COMMONVALUE_H
