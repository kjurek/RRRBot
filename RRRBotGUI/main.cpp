#include "rrrbotapplication.h"
#include <QtWidgets/QApplication>
#include <qmessagebox.h>

int main(int argc, char *argv[])
{
	try{
		QApplication a(argc, argv);
		RRRBotApplication w;
		w.show();
		return a.exec();
	}
	catch (std::exception& e)
	{
		QString msg = e.what();
		QMessageBox::information(nullptr, "", msg);
	}
}
