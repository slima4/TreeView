#-------------------------------------------------
#
# Project created by QtCreator 2013-03-26T20:01:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    itemmodel.cpp \
    item.cpp \
    checkboxdelegate.cpp \
    stardelegate.cpp \
    stareditor.cpp \
    starrating.cpp \
    progressdelegate.cpp \
    progress.cpp

HEADERS  += mainwindow.h \
    itemmodel.h \
    item.h \
    checkboxdelegate.h \
    stardelegate.h \
    stareditor.h \
    starrating.h \
    progressdelegate.h \
    progress.h

FORMS    += mainwindow.ui
