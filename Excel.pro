
TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = excel \
          sample \
          test
          
libDir.commands = mkdir lib

QMAKE_EXTRA_TARGETS += libDir
