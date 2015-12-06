#-------------------------------------------------
#
# Project created by QtCreator 2014-03-11T09:38:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CLI
TEMPLATE = app


SOURCES +=  ../sources/main.cpp \
            ../sources/mainwindow.cpp \
            ../sources/output.cpp \
            ../sources/input.cpp \
            ../sources/mycli.cpp \
            ../sources/listener.cpp

HEADERS +=  ../sources/mainwindow.h \
            ../sources/output.h \
            ../sources/input.h \
            ../sources/mycli.h \
            ../sources/listener.h

FORMS +=    ../sources/mainwindow.ui

INCLUDEPATH +=  ../../../delivery/CloudBuilder/Headers \
                ../../../CloudBuilder/tests/

CONFIG(debug, debug|release){
LIBS +=     -L../../../delivery/CloudBuilder/Windows/Debug_VS2012/ \
            -L../../../CloudBuilder/tests/libCLI/libCLI_win32/Debug/ }
CONFIG(release, debug|release){
LIBS +=     -L../../../delivery/CloudBuilder/Windows/Release_VS2012/ \
            -L../../../CloudBuilder/tests/libCLI/libCLI_win32/Release/ }

LIBS +=     -lCloudBuilder \
            -llibCLI
