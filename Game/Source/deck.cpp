/*
 * Arcomage Tribute
 *
 * File:	deck.cpp
 * Desc: 	Manages a deck of Cards and provides utility functions
 *			like random card selection.
 *
 * Date: 	07/2007
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
#include "deck.h"

#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <AeonCompress.h>

#include "utility.h"

#include "ZIPFile.h"

namespace arcomage {

	// -------------------------------------------------------------------------
	// Constructor
	Deck::Deck(const char* file, Arcomage* pGame)
		: gen(static_cast<unsigned>(std::time(0)) ^
		0xDEADBEEF), archive(Aeon::AeonCompress::createZipFile(std::
		string(DECK_PATH).append(file)))
	{
		game = pGame;
		bool template_default = true;

		UIManager::getInstance()->clearCards();
		UIManager::getInstance()->deleteComponent(IMAGE,
			"card_darkened.png");
		UIManager::getInstance()->deleteComponent(IMAGE,
			"card_darkened.png");
		UIManager::getInstance()->deleteComponent(IMAGE,
			"card_darkened.png");

		// build path
		std::string path = "";
		path.append(DECK_PATH).append(file);


		if(archive->getLastError() != Aeon::Compress::ZIP_NONE) {
			Utility::getInstance()->exitError("Error opening Deck Archive.");
		}

		DeckPreview* preview = new DeckPreview(archive, std::string(file));

		if (preview->getMetaData("Template") != "default") {
			template_default = false;
		}

		std::string deck_file = "";
		deck_file.append(DECK_PATH).append(file);

		Utility::getInstance()->logMessage("arcomage.log",
			std::string(
			"[arcomage::Deck] Got request for ")
			.append(path).c_str());

		Utility::getInstance()->logMessage("arcomage.log",
			std::string("[arcomage::Deck] Reading Meta Information of '")
			.append(preview->getMetaData("Name"))
			.append("' by ")
			.append(preview->getMetaData("Author")).c_str());

		Utility::getInstance()->logMessage("arcomage.log",
			std::string("[arcomage::Deck] Deck Meta Information: ")
			.append(preview->getMetaData("Generator"))
			.append(" Version=")
			.append(preview->getMetaData("Version"))
			.append(" Date=")
			.append(preview->getMetaData("Date")).c_str());

		num_cards = 0;

		// Load the Template Images
		UIManager::getInstance()->addComponent(IMAGE,
			archive, "template/images/card_darkened.png", 0, 0, state_GAME,
			false);
		UIManager::getInstance()->addComponent(IMAGE,
			archive, "template/images/card_mouseover.png", 0, 0, state_GAME,
			false);
		UIManager::getInstance()->addComponent(IMAGE,
			archive, "template/images/general_backside.png", 0, 0,
			state_GAME, false);

		this->loadCards();
		assert(num_cards >= 6);

		bool isondeck = false;
		for (int i = 0; i<6; i++) {
			do {
				visible[i] = randomCard();
				isondeck = true;
				for (int j = 0; j<i; j++) {
					if (visible[j]==visible[i]) {
						isondeck = false;
					}
				}
			} while (!isondeck);
		}


		UIManager::getInstance()->setVisibleCards(visible);

	}

	// -------------------------------------------------------------------------
	Deck::~Deck()
	{
		std::map<const int, Card*>::iterator it;
		for(it = cards.begin(); it != cards.end();
			it++) {
			if(it->second !=0) {
				delete it->second;
				it->second = 0;
			}
		}
		cards.clear();
	}

	// -------------------------------------------------------------------------
	// Load Cards
	void Deck::loadCards()
	{

		TiXmlDocument doc;
		doc.Parse(archive->unpackAsString("data/deck.xml").c_str());

		std::string progress = "";

		TiXmlElement* root = doc.RootElement();
		for (TiXmlElement* element = root->FirstChildElement("Card");
			element; element = element->NextSiblingElement("Card")) {
			num_cards++;
		}
		Utility::getInstance()->logMessage(
			"arcomage.log", std::string("[arcomage::Deck] Found ")
			.append(to_string(num_cards))
			.append(" card definitions.").c_str());

		for (int i = 1; i<=num_cards; i++) {
			progress = "";
			progress.append("Loading Deck (").append(to_string(i))
				.append(" of ")
				.append(to_string(num_cards))
				.append(" cards loaded)");

			int perc = i;
			perc = perc*(100/num_cards);
			if(perc % 30 == 0) {
				game->updateProgress(progress, perc);
				game->update();
			}

			cards[i] = new Card(i, archive);
			if(cards[i]->getScript().compare("0") != 0) {
				scripts[i] = archive->unpackAsString("scripts/"+
					cards[i]->getScript());
			}
		}

	}
	// -------------------------------------------------------------------------
	// Signal: clicked
	bool Deck::clicked(int card_id)
	{
		if (cards[card_id]->isDarkened()) {
			return false;
		} else {
			return true;
		}
	}

	// -------------------------------------------------------------------------
	// Signal: discard
	void Deck::discard(int card_id)
	{
		randomize(card_id);
	}

	// -------------------------------------------------------------------------
	// Returns a random card number
	int Deck::randomCard()
	{
		boost::uniform_int<> dist(1, num_cards);
		boost::variate_generator<boost::mt19937&,
			boost::uniform_int<> > die(gen, dist);
		return die();
	}

	// -------------------------------------------------------------------------
	// Randomize
	void Deck::randomize(int current)
	{
		bool isondeck = false;

		int pos = 0;

		for (int i = 0; i<6; i++) {
			if (visible[i] == current)
				pos = i;
		}

		do {
			visible[pos] = randomCard();
			isondeck = true;
			for (int j = 0; j<6; j++) {
				if (j != pos && visible[j]==visible[pos]) {
					isondeck = false;
				}
			}
		} while (!isondeck);

		UIManager::getInstance()->setVisibleCards(visible);
	}
	// -------------------------------------------------------------------------
	// Update
	void Deck::update(int bricks, int gems, int beasts)
	{
		for (int i = 0; i<6; i++) {
			cards[visible[i]]->setDarkened(true);
			UIManager::getInstance()->setCardDarkened(visible[i], true);
			if (cards[visible[i]]->checkRequirements(bricks, gems, beasts)) {
				cards[visible[i]]->setDarkened(false);
				UIManager::getInstance()->setCardDarkened(visible[i], false);
			}
		}
	}
	// -------------------------------------------------------------------------
	// Get Card Data
	int Deck::getValueFromCard(int card_num, std::string attrib)
	{
		return cards[card_num]->getValue(attrib);
	}

	// -------------------------------------------------------------------------
	bool Deck::getAdditionalTurn(int card_num)
	{
		return cards[card_num]->additionalTurn();
	}

	// -------------------------------------------------------------------------
	std::string Deck::getScript(int id)
	{
		return cards[id]->getScript().compare("0") == 0 ? "0" : this->
			scripts[id];
	}

}
