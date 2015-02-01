#-------------------------------------------------
#
# Project created by QtCreator 2015-01-31T17:48:40
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = TIDTest
CONFIG   += console c++11
CONFIG   -= app_bundle
unix: LIBS += -lcppunit

TEMPLATE = app


SOURCES += main.cpp \
    Network/NetworkBalancer.cpp

HEADERS += \
    Network/NetworkBalancer.hpp
