/*
 * Arcomage Tribute
 *
 * File:	deckpreview.cpp
 * Desc: 	Reads the XML-Metadata of a *.deck-File using the DeckStorage class
 *			and provides a set of meta information as Strings.
 *
 * Date: 	12/2008
 *
 * Copyright (C) 2007 - 2010 Xography. <www.gatewayheaven.com>
 *
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
 */
#include "deckpreview.h"

#include "txml/tinyxml.h"
#include "defines.h"
#include "ZipFile.h"
#include <sstream>
#include <iostream>

namespace arcomage {

	// -------------------------------------------------------------------------
	DeckPreview::DeckPreview(Ptr<Aeon::ZipFile> archive, const std::string &filename)
	{
		TiXmlDocument doc;
		doc.Parse(archive->unpackAsString("meta.xml").c_str());

		TiXmlElement* root = doc.RootElement();
		TiXmlElement* tmp;

		meta["Filename"] = filename;

		// Read the Deck Meta information
		tmp = root->FirstChildElement("Deck");
		meta["Version"] = root->Attribute("VersionAPI");
		meta["Generator"] = root->Attribute("GeneratedBy");
		meta["Template"] = root->Attribute("Template");

		// Read the Deck info
		tmp = root->FirstChildElement("Name");
		meta["Name"] = tmp->FirstChild()->ToText()->Value();
		tmp = root->FirstChildElement("Description");
		meta["Description"] = tmp->FirstChild()->ToText()->Value();
		tmp = root->FirstChildElement("Author");
		meta["Author"] = tmp->FirstChild()->ToText()->Value();
		tmp = root->FirstChildElement("Version");
		meta["Version"] = tmp->FirstChild()->ToText()->Value();
		tmp = root->FirstChildElement("Date");
		meta["Date"] = tmp->FirstChild()->ToText()->Value();

		meta["File"] = "\\data\\deck.xml";

		// count cards

		TiXmlDocument doc_2;

		doc_2.Parse(archive->unpackAsString("data/deck.xml").c_str());

		int num_cards = 0;

		TiXmlElement* root_2 = doc_2.RootElement();
		for (TiXmlElement* element = root_2->FirstChildElement("Card");
			element; element = element->NextSiblingElement("Card")) {
			num_cards++;
		}

		std::stringstream strs;
		strs << num_cards;
		meta["Cards"] = strs.str();
	
	}


	// -------------------------------------------------------------------------
	const std::string& DeckPreview::getMetaData(const std::string& entry)
	{
		return meta[entry];
	}

}
