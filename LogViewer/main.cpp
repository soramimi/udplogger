
#include <QApplication>
#include "Logger.h"
#include "MainWindow.h"

int main(int argc, char **argv)
{
	Logger::initialize();
	QApplication a(argc, argv);
	qRegisterMetaType<LogItem>();
	MainWindow w;
	w.show();
	int r = a.exec();
	Logger::cleanup();
	return r;
}

