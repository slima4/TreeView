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
    progressdelegate.cpp \
    checkboxitem.cpp \
    progressitem.cpp

HEADERS  += mainwindow.h \
    itemmodel.h \
    item.h \
    checkboxdelegate.h \
    progressdelegate.h \
    checkboxitem.h \
    progressitem.h

FORMS    += mainwindow.ui
