/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	CardEditor.h
 * Desc: 	Custom OgreWidget, enabling the user to edit a deck of cards.
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
#ifndef _CardEditor_h_
#define _CardEditor_h_
#include "EditorWidget.h"
#include "ui_CardEditor.h"

class OgreWidget;
#include "ArcomageForward.h"


/**
 * @brief Editor Widget with full-fledged capabilities to edit Card Decks.
 * Enables the user to edit the Card Deck of a given EditorProject, with the
 * possibility to modify/delete existing Cards and add new ones.
 *
 * @note Please note that the Card Deck is directly modified in the given
 * project's instance, but the user has to confirm changes first.
 * @see EditorProject
 */ 
class CardEditor : public QWidget, public EditorWidget {
	Q_OBJECT

public:
	/**
	 * Constructs an Editor with a given Project and the parent DeckEditor
	 * (which should have instantiated this class).
	 *
	 */ 
	CardEditor(EditorProject* project, DeckEditor* parentEditor, QWidget *parent = 0, Qt::WFlags flags = 0);
	~CardEditor();

	/**
	 * Prepares the UI Definitions and Stylesheets for the live 3D Render-Preview.
	 * @note This method has to be called in order to be able to edit cards.
	 */
	void loadEditorResources();

	/**
	 * Unloads all Resources used by the editor and disables UI Rendering in 3D Space.
	 *
	 * @note This method does also a project-cleanup, so calling the EditorsProject
	 * cleanup functionality is not required.
	 */
	void releaseEditorResources();

	/**
	 * Resets the Editing area to its respective default values.
	 */
	void reset();

	/**
	 * Fills the editing area with the given Cards' values and renders it into
	 * the Preview window.
	 *
	 * @param card the Card to display.
	 */ 
	void display(Arcomage::Card* card);

	/**
	 * Renders a given card into the Preview window.
	 * @param 
	 */ 
	void updateCardDisplay(Arcomage::Card* card);

	/**
	 * Attempt to modify the actual Card, writing all changes from the editing
	 * fields into the Object.
	 */
	bool storeCardChanges();

	/**
	 * Returns the current Editor Project.
	 *
	 * @return the current EditorProject
	 */ 
	EditorProject* getProject() { return _project; }

	void populateTree();

	void setProject(EditorProject* project);
public slots:
	void treeItemClicked(const QModelIndex& index);
	void resetChanges();
	void applyChanges();
	void changeCardType();
	void captionChanged();
	void requirementsChanged();
	void nameChanged();
	void somethingChanged();
	void validateValues();
	void selectImage();

	// Card Operations
	void removeCard();
	void addCard();

private:
	Ui::CardEditor ui;
	OgreWidget* widget;
	Arcomage::CardVector& cards;
	Arcomage::Card* current;
	bool hasChanged;
	bool notified;
	QTreeWidgetItem* currentItem;
	int cardCount;
	QString lastDirectory;
	bool rsError;

	// Sets up QT connections for the UI components
	void connectUI();

	// Adds a Card to the list at the given index
	void addCardToList(Arcomage::Card* card, int index);
};

#endif