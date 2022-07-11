#include "editwindow.h"
#include "blockwidget.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BlockWidget bw("Add","Add two number",{"n1"});
    bw.show();

    return a.exec();
}
