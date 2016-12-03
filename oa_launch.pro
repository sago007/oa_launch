#-------------------------------------------------
#
# Project created by QtCreator 2016-12-02T22:03:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = oa_launch
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/OpenArenaLaunch.cpp

HEADERS  += src/mainwindow.h \
    src/OpenArenaLaunchh.h \
    src/platform_things.h

FORMS    += forms/mainwindow.ui
