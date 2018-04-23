/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	ProjectWizard.h
 * Desc: 	A Wizard to guide the user through the creation of a new project
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
#ifndef _ProjectWizard_h_
#define _ProjectWizard_h_

#include <QWizard>
#include <QtGui>
#include "ui_ProjectWizard.h"

class EditorProject;

/**
 * @brief Qt Wizard (QWizard) which guides the user through the creation of a new Deck.
 */ 
class ProjectWizard : public QWizard
{
	Q_OBJECT
public:

	ProjectWizard(EditorProject* project, QWidget *parent = 0);

private slots:
	void browseLocation();

private:
	Ui::ProjectWizard ui;

};


#endif