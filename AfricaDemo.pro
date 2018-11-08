#-------------------------------------------------
#
# Project created by QtCreator 2016-08-11T15:59:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = HmiApplication
TEMPLATE = app
TARGET = AfricaDemo

SOURCES += main.cpp\
        mainwindow.cpp \
    Core/CXAbstractWidget.cpp \
    pagealltop.cpp \
    tcmscomm/cl1_1.c \
    tcmscomm/host_dep.c \
    tcmscomm/tcmscontroller.cpp \
    tcmscomm/tcmsport.cpp \
    tcmscomm/tcmsAfricaTimebuffer.cpp \
    tcmscomm/tcmsAfricabuffer.cpp \
    pagegeneral.cpp \
    components/scalepawidget.cpp \
    components/analogclockwidget.cpp \
    components/scaleaccwidget.cpp \
    components/notchbarwidget.cpp \
    components/scalebarwidget.cpp \
    components/scaleunitwidget.cpp \
    components/scalecontentwidget.cpp \
    Logic/logic_page_alltop.cpp \
    tcmscomm/tcmsHMIAfricabuffer.cpp

HEADERS  += mainwindow.h \
    Core/CXAbstractWidget.h \
    pagealltop.h \
    tcmscomm/cl1_1.h \
    tcmscomm/cl1_ret.h \
    tcmscomm/config.h \
    tcmscomm/dpr_dep.h \
    tcmscomm/host_dep.h \
    tcmscomm/mvb.h \
    src/disphw32.h \
    src/windefs.h \
    tcmscomm/tcmscontroller.h \
    tcmscomm/tcmsport.h \
    tcmscomm/tcmsAfricaTimebuffer.h \
    tcmscomm/tcmsAfricabuffer.h \
    pagegeneral.h \
    components/scalepawidget.h \
    components/analogclockwidget.h \
    components/scaleaccwidget.h \
    components/notchbarwidget.h \
    components/scalebarwidget.h \
    components/scaleunitwidget.h \
    components/scalecontentwidget.h \
    Logic/logic_page_alltop.h \
    tcmscomm/tcmsHMIAfricabuffer.h

FORMS    +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/src/release/ -lenvcon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/src/debug/ -lenvcon
else:unix: LIBS += -L$$PWD/src/ -lenvcon

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/src/release/envcon.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/src/debug/envcon.lib
else:unix: PRE_TARGETDEPS += $$PWD/src/libenvcon.a
