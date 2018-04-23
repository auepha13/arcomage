#include "Launcher.h"
#include <QtGui/QApplication>
#include "OptionsDialog.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	if(a.arguments().contains("-options")) {
		OptionsDialog o;
		o.show();
		return a.exec();
	} else {
		Launcher w;
		w.show();
		return a.exec();
	}
}
