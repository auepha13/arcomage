/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	EditorProject.h
 * Desc: 	Represents a Deck Project providing importing/exporting features.
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
#ifndef _ProjectARCOMAGEEDITOR_h_
#define _ProjectARCOMAGEEDITOR_h_
#include "DeckMetaData.h"
#include "Card.h"
#include "Deck.h"


class EditorProject {
public:
	EditorProject();
	
	/**
	 * Creates a new Project with existing data, if creating a new Deck, use 
	 * the default constructor and prepare the required data manually.
	 * 
	 * @note the given Card Data is being copied into the Project, so the
	 * loader can be destroyed safely.
	 *
	 * @param data the Deck Meta Data of the existing Project
	 * @param v The card vector (copy).
	 */ 
	EditorProject(Arcomage::DeckMetaData* data, Arcomage::CardVector v);

	~EditorProject();

	/**
	 * Prepare the project for usage, caching all existing data.
	 *
	 * @note This method has the be called before attempting to edit
	 * existing Deck files.
	 */
	void prepare();

	/**
	 * Clean up all data cached by the current project.
	 */
	void cleanUp();

//	void export(DeckExporter* exporter);

	/**
	 * Check whether the current project was created with an outdated version
	 * of the Deck Editor using an old API version.
	 * This enables the Editor to iniate a 'legacy' mode with a compatibility
	 * layer for the old API versions to allow loading existing decks, preventing
	 * the old data to become unusable.
	 *
	 * @return whether the deck's API is outdated or not
	 */ 
	bool isLegacyDeck();

	Arcomage::DeckMetaData* getDeckMetaData() { return data; }
	Arcomage::CardVector& getCards() { return cards; }

	/**
	 * Get the Working Path (not the filename!) of the Project.
	 * The working Path is either within the Editor's cache or a user-specified
	 * path in the filesystem.
	 *
	 * @return the path
	 */ 
	const std::string& getWorkingPath() {
		return projectWorkingPath;
	}

	/**
	 * Get a copy of the Projects' filename.
	 * @return the filename, empty if the project hasn't been saved yet.
	 */
	std::string getFilename();


private:
	Arcomage::DeckMetaData* data;
	Arcomage::CardVector cards;
	std::string projectWorkingPath;
};
#endif