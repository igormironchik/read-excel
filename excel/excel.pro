
TEMPLATE = lib
TARGET = Excel
DESTDIR = ../lib
INCLUDEPATH += . ..
CONFIG += staticlib c++11
QT -= gui core

HEADERS += compoundfile/compoundfile.hpp \
           compoundfile/compoundfile_exceptions.hpp \
           compoundfile/directory.hpp \
           compoundfile/header.hpp \
           compoundfile/msat.hpp \
           compoundfile/sat.hpp \
           compoundfile/compoundfile_stream.hpp \
           compoundfile/utils.hpp \
           bof.hpp \
           book.hpp \
           cell.hpp \
           exceptions.hpp \
           formula.hpp \
           record.hpp \
           sheet.hpp \
           sst.hpp \
           stream.hpp \
           string.hpp

SOURCES += compoundfile/compoundfile.cpp \
	compoundfile/compoundfile_exceptions.cpp \
	compoundfile/directory.cpp \
	compoundfile/header.cpp \
	compoundfile/msat.cpp \
	compoundfile/sat.cpp \
	compoundfile/compoundfile_stream.cpp \
	compoundfile/utils.cpp \
	bof.cpp \
	book.cpp \
	cell.cpp \
	exceptions.cpp \
	formula.cpp \
	record.cpp \
	sheet.cpp \
	sst.cpp \
	stream.cpp \
	string.cpp
