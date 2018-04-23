/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	ToolkitUtil.cpp
 * Desc: 	A Set of common utility functions.
 *
 * Date: 	01/2011
 *
 * Copyright (C) 2007 - 2011 Xography. <www.gatewayheaven.com>
 *
 * -----------------------------------------------------------------------------
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * -----------------------------------------------------------------------------
 */
#include "ToolkitUtil.h"
#include <QApplication>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <QProcess>

// -----------------------------------------------------------------------------
void ToolkitUtil::notifyError(const QString &msg) {
	QApplication::alert(qApp->activeWindow());
	QMessageBox::critical(qApp->activeWindow(), "", msg,
		QMessageBox::Ok, QMessageBox::Ok);
}

// -----------------------------------------------------------------------------
void ToolkitUtil::notify(const QString &msg) {
	QApplication::alert(qApp->activeWindow());
	QMessageBox::information(qApp->activeWindow(), "", msg,
		QMessageBox::Ok, QMessageBox::Ok);
}

// -----------------------------------------------------------------------------
void ToolkitUtil::exitError(const QString &msg) {
	QApplication::alert(qApp->activeWindow());
	QMessageBox::critical(qApp->activeWindow(), "Fatal Error occurred", 
		"Fatal error occurred. The application is unable to continue execution and has to shut down. \n\n Please report the error to the authors!\n\nThe following error triggered the crash: \n"
		+msg,
		QMessageBox::Ok, QMessageBox::Ok);
	// Dump logs
	// ToolkitAppManager::dumpLogs();

	// Attempt emergency save 
	// ToolkitAppManager::notifyEmergencySave();

	// fire error report and terminate the app.
	/*
	QProcess* proc = new QProcess(0);
	QStringList cmd;
	cmd.append("report.dmp");
	cmd.append("Error/config.xml");

	proc->startDetached("ErrorReportingTool.exe", cmd);
	*/
	//qApp->exit(EXIT_FAILURE);
	exit(EXIT_FAILURE);
}
