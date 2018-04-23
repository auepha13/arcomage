/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	AtlasGenerator.h
 * Desc: 	Utility class to help generate Texture Atlasses from a number of 
 *			image files.
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
#ifndef _AtlasGenerator_h_
#define _AtlasGenerator_h_

#include "ArcomageForward.h"

/**
 * @brief Utility class to allow generation of texture Atlasses (= compiling many
 * single image files into one large file for the sake of performance).
 */ 
class AtlasGenerator{
public: 
	/**
	 * Constructs an Atlas Generator with a reference to a deck of cards.
	 * The Generation can take any time, but if the deck changes, updateReference()
	 * has to be called.
	 *
	 * @param reference to the current deck of cards.
	 */ 
	AtlasGenerator(Arcomage::CardVector& cards);

	/**
	 * Generates a temporary legacy atlas and stores it in the Editor's cache directory.
	 * The Legacy atlas is more of a pseudo StyleSheet which references single image
	 * files instead of areas one large file, since outdated decks did not ship
	 * with compiled texture Atlasses.
	 *
	 */ 
	void generateLegacyAtlas();

	
	void addFile(const std::string& file);

	/**
	 * Intended as convenience function to allow continuous usage of the already
	 * created Instance, even when the initial card deck gets dereferenced / destroyed.
	 *
	 * @param the new reference.
	 */ 
	void updateReference(Arcomage::CardVector& cards);
private:
	Arcomage::CardVector& deck;
};

#endif