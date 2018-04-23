/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	EditorProject.cpp
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
#include "EditorProject.h"
#include "PackUtil.h"
#include <iostream>
#include <fstream>
#include "ToolkitUtil.h"
#include <OgreResourceGroupManager.h>

#include "ToolkitUtil.h"
#include "AtlasGenerator.h"
#include <boost/filesystem.hpp>



// -----------------------------------------------------------------------------
EditorProject::EditorProject() 
	: data(new Arcomage::DeckMetaData()) {

}

// -----------------------------------------------------------------------------
EditorProject::EditorProject(Arcomage::DeckMetaData* data, Arcomage::CardVector v) 
	: data(data), 
	cards(v),
	projectWorkingPath("Editor/Cache/"+Util::extractFilename(data->getMetaData("Filename"))) {

}

// -----------------------------------------------------------------------------
EditorProject::~EditorProject() {
	std::string rgName = "Interface"+Util::extractFilename(data->getMetaData("Filename"));
	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(rgName);
	boost::filesystem::remove (projectWorkingPath);
}
// -----------------------------------------------------------------------------
void EditorProject::prepare() {
	PackUtil::unpack(data->getMetaData("Filename"), projectWorkingPath);

	if(isLegacyDeck()) {
		AtlasGenerator atlas(cards);
		atlas.generateLegacyAtlas();
	} else {
		if (boost::filesystem::exists ("Editor/Cache/atlas.cache"))
				boost::filesystem::remove ("Editor/Cache/atlas.cache");

		boost::filesystem::copy_file (projectWorkingPath+"/template/atlas.def", "Editor/Cache/atlas.cache");
	}

	// Add Resource Location for temporary Images
	Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();
	std::string rgName = "Interface"+Util::extractFilename(data->getMetaData("Filename"));
	rgm.addResourceLocation(projectWorkingPath+"/images", "FileSystem",rgName);
	rgm.initialiseResourceGroup(rgName);
}
// -----------------------------------------------------------------------------
void EditorProject::cleanUp() {
	if (boost::filesystem::exists ("Editor/Cache/atlas.cache"))
		boost::filesystem::remove ("Editor/Cache/atlas.cache");

	if (boost::filesystem::exists (projectWorkingPath))
		boost::filesystem::remove_all(projectWorkingPath);
}

// -----------------------------------------------------------------------------
bool EditorProject::isLegacyDeck() {
	// Decks generated with the old API are Version < 1.0 and considered
	// legacy.
	return data->getMetaData("VersionAPI") == "1.0";
}

// -----------------------------------------------------------------------------
std::string EditorProject::getFilename() {
	return boost::filesystem::path(data->getMetaData("Filename")).filename();
}