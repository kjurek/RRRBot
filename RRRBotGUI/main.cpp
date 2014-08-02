#include "rrrbotapplication.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	RRRBotApplication w;
	w.show();
	return a.exec();
}
