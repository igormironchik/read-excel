
TEMPLATE = subdirs

CONFIG += ordered

SUBDIRS = stream \
	testdocument \
	bof \
	book \
	cell \
	compoundfile \
	formula \
	header \
	record \
	sst \
	string \
	datetime \
	complex

HEADERS += helper/helper.hpp
