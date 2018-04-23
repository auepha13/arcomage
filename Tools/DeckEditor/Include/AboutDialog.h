/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	AboutDialog.h
 * Desc: 	The About dialog
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
#ifndef _AboutDialog_h_
#define _AboutDialog_h_
#include "ui_AboutDialog.h"

#include "ToolkitUtil.h"
#include "DeckEditor.h"

class AboutDialog : public QDialog {

	Q_OBJECT

public:
	AboutDialog(QWidget * parent = 0, Qt::WindowFlags flags = 0) 
	: QDialog(parent, flags) {
		ui.setupUi(this);
		ui.version->setText(Util::toQString(DeckEditor::VersionString));
	}


private:
	Ui::AboutDialog ui;
};

#endif