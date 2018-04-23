/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	MetaDataEditor.h
 * Desc: 	Editor Widget to allow modifcation of a given projects' metadata 
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
#ifndef _MetaDataEditor_
#define _MetaDataEditor_
#include "EditorWidget.h"
#include "ui_DeckMetaData.h"
#include <QWidget>
#include "ArcomageForward.h"


/**
 * @brief Allows the user to modify or add meta data to the deck such as a name,
 * an author, a version and a short description.
 */ 
class MetaDataEditor : public QWidget, public EditorWidget {
	Q_OBJECT

public:
	MetaDataEditor(EditorProject* project, DeckEditor* parentEditor, 
					QWidget *parent = 0, Qt::WFlags flags = 0);
	~MetaDataEditor();

	void setProject(EditorProject* project);

private slots:
	void displayMetaData();
	void updateMetaData();
	void changed();

private:
	Ui::MetaData ui;
	Arcomage::DeckMetaData* data;
};
#endif