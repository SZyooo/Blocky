#include "innerwidget.h"
#include<QEvent>
#include<QHoverEvent>

InnerWidget::InnerWidget()
{
    setAttribute(Qt::WA_Hover,true);
    setMouseTracking(true);
    installEventFilter(this);
}

bool InnerWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::HoverMove)
    {
        QHoverEvent* he = static_cast<QHoverEvent*>(event);
        _mouse_pos = he->pos();
    }
    return QWidget::eventFilter(watched,event);
}
