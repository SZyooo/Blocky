QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    blockwidget.cpp \
    commonvalue.cpp \
    conditionwidget.cpp \
    editwidget.cpp \
    inputwidget.cpp \
    lbwidget.cpp \
    legowidget.cpp \
    loopsegmentwidget.cpp \
    main.cpp \
    editwindow.cpp \
    segmentcontainerwidget.cpp \
    tool.cpp

HEADERS += \
    blockwidget.h \
    commonvalue.h \
    conditionwidget.h \
    editwidget.h \
    editwindow.h \
    inputwidget.h \
    lbwidget.h \
    legowidget.h \
    loopsegmentwidget.h \
    segmentcontainerwidget.h \
    tool.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
