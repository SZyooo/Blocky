#include "editwindow.h"
#include "tool.h"
#include <QApplication>
#include "variablelist.h"
#include "blocklistwidget.h"
#include "blockwidget.h"
#include "legowidget.h"
#include "blockbox.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EditWindow ew;
    ew.show();
    return a.exec();
}
