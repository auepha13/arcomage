/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	DeckEditor.h
 * Desc: 	Deck Editor Main class, serving as Mainwindow
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
#ifndef DECKEDITOR_H
#define DECKEDITOR_H

#include <QtGui/QMainWindow>
#include "ui_deckeditor.h"
#include "OgreSystem.h"

class CardEditor;
class MetaDataEditor;

/**
 * @brief The Mainwindow of the Editor.
 * The Editor's MainWindow contains all actions (bound to menu and toolbar) as 
 * well as the respective Editors, contained in a dynamic Tab Widget.
 *
 */
class DeckEditor : public QMainWindow
{
	Q_OBJECT

public:
	DeckEditor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~DeckEditor();

	// Static members, to centralize Version-Management the dumb way
	static std::string Version;
	static std::string VersionString;

	/**
	 * Enables Widgets placed in Tabs to notify its parent about a change in
	 * their respective document.
	 */ 
	void notifyDocumentChanged();

public slots:
	/**
	* Timer slot, each tick updates the internal Ogre Rendersystem.
	*/
	void tick();

	/**
	 * Slot triggered by the File Open Dialog which handles Deck loading logic.
	 */
	void loadDeck();

	/**
	 * Displays the "About" Dialouge
	 */
	void about();

	void exitProgram();

	void reportBug();
	void projectWebsite();
	void exportDeck();

	void saveProject();
	void saveProjectAs();
	void closeCurrentProject();
	void newProject();
	void uploadDeck();

protected:
	/**
	 * Overrides the default closeEvent and catches the close action to ask
	 * the user whether they wish to save their modifications (if any were made).
	 */
	void closeEvent(QCloseEvent *event);

private:
	CardEditor* editor;
	MetaDataEditor* metaEditor;

	Ui::DeckEditorClass ui;
	QWidget* widget;
	QTimer* timer;
	OgreSystem& ogreSystem;

	bool remindLegacyDeck;
	bool documentChanged;
	bool isProject;
	QString lastFile;
};

#endif // DECKEDITOR_H
