
TEMPLATE = lib
TARGET = testdocument
DESTDIR = ../../lib
CONFIG += staticlib
QT -= gui core

HEADERS += document.hpp

SOURCES += document.cpp

INCLUDEPATH += . $$PWD/../../
DEPENDPATH += . $$PWD/../../
