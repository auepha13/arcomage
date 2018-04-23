/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	RendersystemSelection.h
 * Desc: 	Simple drop-down selection QT Widget to enable the user to choose
 *			a Rendersystem.
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
#ifndef _RendersystemSelection_h_
#define _RendersystemSelection_h_
#include "ui_RendersystemSelection.h"
#include <OgrePrerequisites.h>
#include <OgreRoot.h>

#include <QDialog>

/**
 * @brief Dialog to let the user select an OGRE RenderSystem from a list.
 */
class RendersystemSelection : public QDialog {

	Q_OBJECT

public:
	RendersystemSelection(const Ogre::RenderSystemList& rsList, 
		QWidget * parent = 0, Qt::WindowFlags flags = 0);

protected:
	void closeEvent(QCloseEvent *event);
private slots:
		void ok();
private:
	Ui::RendersystemSelection ui;
};

#endif