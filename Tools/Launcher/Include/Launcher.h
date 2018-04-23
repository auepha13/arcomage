#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QtGui/QMainWindow>
#include "ui_Launcher.h"

class Launcher : public QMainWindow
{
	Q_OBJECT

public:
	Launcher(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Launcher();

private slots:
	void options();
	void website();
	void quitLauncher();
	void startGame();
	void startEditor();
protected:
     void paintEvent(QPaintEvent *e);
private:
	Ui::LauncherClass ui;
};

#endif // LAUNCHER_H
