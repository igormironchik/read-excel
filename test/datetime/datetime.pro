
TEMPLATE = app
DESTDIR = ../..
CONFIG += console
QT -= gui core

SOURCES += main.cpp

INCLUDEPATH += . $$PWD/../../
DEPENDPATH += . $$PWD/../../

include( ../../excel/excel.pri )
