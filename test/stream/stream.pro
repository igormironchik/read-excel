
TEMPLATE = lib
TARGET = teststream
DESTDIR = ../../lib
CONFIG += staticlib
QT -= gui core

HEADERS += stream.hpp

SOURCES += stream.cpp

INCLUDEPATH += . $$PWD/../../
DEPENDPATH += . $$PWD/../../
