#include "analyze.h"
#include <QtWidgets/QApplication>
#include <QDate>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	analyze w;
	w.show();
	return a.exec();
}
