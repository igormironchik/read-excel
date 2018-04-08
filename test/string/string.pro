
TEMPLATE = app
DESTDIR = ../..
CONFIG += console
QT -= gui core

SOURCES += main.cpp

INCLUDEPATH += . $$PWD/../../
DEPENDPATH += . $$PWD/../../

include( ../../excel/excel.pri )

unix|win32: LIBS += -L$$OUT_PWD/../../lib/ -lteststream

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../lib/teststream.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../lib/libteststream.a
