/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	RendersystemSelection.cpp
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
#include "RendersystemSelection.h"
#include <OgreRoot.h>
#include <OgreRenderSystem.h>
#include <OgreRenderWindow.h>
#include <OgreConfig.h>
#include <OgreConfigFile.h>
#include <OgreRoot.h>
#include "ToolkitUtil.h"
#include "OgreSystem.h"

#include <QtEvents>

RendersystemSelection::RendersystemSelection(const Ogre::RenderSystemList& rsList,
											QWidget * parent, 
											Qt::WindowFlags flags) 
											: QDialog(parent, flags) {
	ui.setupUi(this);

	if(rsList.size() == 0) {
		ui.rendersystemDropDown->addItem(tr("No applicable Rendersystems found"));
	} else {
		ui.rendersystemDropDown->setEnabled(true);
	}

	for(unsigned int i = 0; i < rsList.size(); i++) {
		ui.rendersystemDropDown->addItem(QString(rsList[i]->getName().c_str()));
	}
	ui.rendersystemDropDown->setCurrentIndex(0);
	
	connect(ui.buttonBox, SIGNAL(accept()), this, SLOT(ok()));
	OgreSystem::getInstance().setRSChoice(Util::toStdString(ui.rendersystemDropDown->currentText()));
}

void RendersystemSelection::ok() {
	OgreSystem::getInstance().setRSChoice(Util::toStdString(ui.rendersystemDropDown->currentText()));
}

void RendersystemSelection::closeEvent(QCloseEvent *event) {

	OgreSystem::getInstance().setRSChoice(Util::toStdString(ui.rendersystemDropDown->currentText()));
	event->accept();
}
