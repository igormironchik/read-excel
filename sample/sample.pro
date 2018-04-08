
TEMPLATE = app
TARGET = sample
DESTDIR = .
CONFIG += console
QT -= core gui

include( ../excel/excel.pri )

SOURCES += main.cpp

INCLUDEPATH += . $$PWD/..
DEPENDPATH += . $$PWD/..
