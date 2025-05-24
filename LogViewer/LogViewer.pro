
TEMPLATE = app
TARGET = udprecv
INCLUDEPATH += .
INCLUDEPATH += ../src
INCLUDEPATH += ../include
QT += core gui widgets

!win32:LIBS += $$PWD/../lib/liblogger.a
win32:LIBS += $$PWD/../lib/logger.lib -lws2_32

HEADERS += \
	../src/htmlencode.h \
	../src/strformat.h \
	LogView.h \
	MainWindow.h \
	main.h \
	toi.h

SOURCES += \
	../src/htmlencode.cpp \
	LogView.cpp \
	MainWindow.cpp \
	main.cpp

FORMS += \
	MainWindow.ui
