#ifndef TOOL_H
#define TOOL_H

#define BDEBUG
class QString;

void Debug(QString s);
class QWidget;
class QColor;
void ChangeBKG(QWidget* w, QColor c);
void SetRadius(QWidget* w, int pix);
void AddRadius(QWidget* w,int value);

void TurnOnShadowEffect(QWidget * w);
void TurnOffShadowEffect(QWidget* w);
QColor FetchAColor();
#endif // TOOL_H
