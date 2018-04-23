/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	DeckExportWizard.h
 * Desc: 	QWizard which guides the user through exporting the Deck.
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
#ifndef _DeckExportWizard_h_
#define _DeckExportWizard_h_

#include <QWizard>
#include <QtGui>
#include "ui_DeckExportWizard.h"
#include "ToolkitUtil.h"

class EditorProject;

/**
 * @brief Wizard to help the user export decks.
 */
class DeckExportWizard : public QWizard
{
	Q_OBJECT
public:

	DeckExportWizard(const QString& previousFilename, EditorProject* project, QWidget *parent = 0);

	void log(const QString& msg);

	 std::string getFile() {
		return Util::toStdString(ui.file->text()).c_str();
	}
	private slots:
		void selectFileName();
		void exportProject();
private:
	Ui::DeckExportWizard ui;
	QString fileName;
	EditorProject* project;
 };


#endif