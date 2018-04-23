#include "Launcher.h"
#include <QtGui>
#include <QDesktopServices>
#include "OptionsDialog.h"
#include <QProcess>

// -----------------------------------------------------------------------------
Launcher::Launcher(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent,  flags)
{
	ui.setupUi(this);
	/*
	QPixmap pixmap(":/Launcher/Resources/background.png");
	QPalette p = ui.centralWidget->palette();
	p.setBrush(QPalette::Base, pixmap);
	ui.centralWidget->setPalette(p);
	ui.centralWidget->resize(pixmap.size());
	*/
	QRect available_geom = QDesktopWidget().availableGeometry();
	QRect current_geom = frameGeometry();
	setGeometry(available_geom.width() / 2 - current_geom.width() / 2,
		available_geom.height() / 2 - current_geom.height() / 2,
		current_geom.width(),
		current_geom.height()
		);

	connect(ui.optionsButton, SIGNAL(clicked()), this, SLOT(options()));
	connect(ui.websiteButton, SIGNAL(clicked()), this, SLOT(website()));
	connect(ui.exitButton, SIGNAL(clicked()), this, SLOT(quitLauncher()));

	connect(ui.startButton, SIGNAL(clicked()), this, SLOT(startGame()));
	connect(ui.deckEditorButton, SIGNAL(clicked()), this, SLOT(startEditor()));

}

// -----------------------------------------------------------------------------
void Launcher::paintEvent(QPaintEvent *e) {
	/*QPainter paint(this);
	paint.drawPixmap(0, 0, QPixmap(":/Launcher/Resources/background.jpg"));
	QWidget::paintEvent(e);
	*/
}

// -----------------------------------------------------------------------------
Launcher::~Launcher()
{

}

// -----------------------------------------------------------------------------
void Launcher::options() {
	OptionsDialog o;
	o.exec();
}

// -----------------------------------------------------------------------------
void Launcher::website() {
	QDesktopServices::openUrl(QUrl("http://www.gatewayheaven.com/projects/arcomage/", QUrl::TolerantMode));
}

// -----------------------------------------------------------------------------
void Launcher::quitLauncher() {
	qApp->exit(EXIT_SUCCESS);
}

// -----------------------------------------------------------------------------
void Launcher::startGame() {
	QProcess proc(this);
	proc.startDetached("ArcomageTribute.exe");
	this->quitLauncher();
}

// -----------------------------------------------------------------------------
void Launcher::startEditor() {
	QProcess proc(this);
	proc.startDetached("ArcomageTributeEditor.exe");
	this->quitLauncher();
}