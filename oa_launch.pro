#-------------------------------------------------
#
# Project created by QtCreator 2016-12-02T22:03:04
#
#-------------------------------------------------

QT       += core gui

lessThan(QT_MAJOR_VERSION, 5): error("requires Qt 5")

QT += widgets

CONFIG += c++11

TARGET = oa_launch
TEMPLATE = app

INCLUDEPATH += $$PWD/src/Libs/include


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/OpenArenaLaunch.cpp

HEADERS  += src/mainwindow.h \
    src/OpenArenaLaunch.h \
    src/platform_things.h \
    src/oa_profiles.h

FORMS    += forms/mainwindow.ui

RESOURCES += \
    oa_launch_resources.qrc
