#include "editwindow.h"

#include <QApplication>
#include "segmentcontainerwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SegmentContainerWidget scw;
    scw.show();
    return a.exec();
}
