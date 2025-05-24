
DESTDIR = $$PWD/lib
TEMPLATE = lib
TARGET = logger
CONFIG += staticlib
CONFIG -= qt

INCLUDEPATH += include

HEADERS += \
	src/htmlencode.h \
	src/strformat.h

SOURCES += \
	src/Logger.cpp \
	src/htmlencode.cpp

