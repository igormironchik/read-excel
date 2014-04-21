
TEMPLATE = app
DESTDIR = ../..
CONFIG += console
QT -= gui core

SOURCES += main.cpp

INCLUDEPATH += . $$PWD/../../
DEPENDPATH += . $$PWD/../../

unix|win32: LIBS += -L$$OUT_PWD/../../lib/ -lExcel -lteststream -ltestdocument

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../lib/Excel.lib \
									$$OUT_PWD/../../lib/teststream.lib \
									$$OUT_PWD/../../lib/testdocument.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../../lib/libExcel.a \
									   $$OUT_PWD/../../lib/libteststream.a \
									   $$OUT_PWD/../../lib/libtestdocument.a
