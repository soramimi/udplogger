
TEMPLATE = app
TARGET = udprecv
INCLUDEPATH += .
INCLUDEPATH += ../src
INCLUDEPATH += ../include
QT += core gui widgets

LIBS += $$PWD/../bin/liblogger.a

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
