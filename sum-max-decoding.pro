#-------------------------------------------------
#
# Project created by QtCreator 2016-02-12T14:24:30
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = sum-max-decoding
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    decoding.cpp \
    util.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    decoding.h \
    util.h

FORMS    += mainwindow.ui
