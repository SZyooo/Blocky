QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addvariabledialog.cpp \
    blockbox.cpp \
    blocklistwidget.cpp \
    blockmimedata.cpp \
    blockwidget.cpp \
    commonvalue.cpp \
    conditionwidget.cpp \
    editwidget.cpp \
    innerwidget.cpp \
    inputwidget.cpp \
    lbwidget.cpp \
    legowidget.cpp \
    loopsegmentwidget.cpp \
    main.cpp \
    editwindow.cpp \
    segmentcontainerwidget.cpp \
    tool.cpp \
    variablelist.cpp \
    variablewidget.cpp

HEADERS += \
    addvariabledialog.h \
    blockbox.h \
    blocklistwidget.h \
    blockmimedata.h \
    blockwidget.h \
    commonvalue.h \
    conditionwidget.h \
    editwidget.h \
    editwindow.h \
    innerwidget.h \
    inputwidget.h \
    lbwidget.h \
    legowidget.h \
    loopsegmentwidget.h \
    segmentcontainerwidget.h \
    tool.h \
    variablelist.h \
    variablewidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
