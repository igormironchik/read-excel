
TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = excel \
          sample \
          test
          
OTHER_FILES += .travis.yml \
	build.rb \
	README.md \
	COPYING
          
libDir.commands = mkdir lib

QMAKE_EXTRA_TARGETS += libDir
