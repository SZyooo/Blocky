#ifndef INNERWIDGET_H
#define INNERWIDGET_H

#include <QWidget>

class InnerWidget : public QWidget
{
    Q_OBJECT
public:
    InnerWidget();
    bool eventFilter(QObject *watched, QEvent *event);
    QPoint MousePos() const {return _mouse_pos;}
signals:
private:
    QPoint _mouse_pos;
};

#endif // INNERWIDGET_H
