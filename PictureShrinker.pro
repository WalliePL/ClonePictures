#-------------------------------------------------
#
# Project created by QtCreator 2014-09-28T13:41:33
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PictureShrinker
TEMPLATE = app


SOURCES += main.cpp\
        pictureshrinkerwidget.cpp \
    pictureshrinker.cpp \
    pictoreshrinkercontroller.cpp

HEADERS  += pictureshrinkerwidget.h \
    pictureshrinker.h \
    pictoreshrinkercontroller.h

FORMS    += pictureshrinkerwidget.ui
