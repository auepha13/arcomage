/*
 * Arcomage Tribute
 *
 * File: deck.h
 * Desc: Manages a deck of cards
 *
 * Date: 07/2007
 *
 * Copyright (C) 2006,2007 Xography. <www.gatewayheaven.com>
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

#ifndef DECK_H_INCLUDED
#define DECK_H_INCLUDED

#include "global.h"
#include "card.h"
#include "game.h"

#include <AeonCore.h>

// for randomization
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

namespace arcomage {

	class Card;
	class Arcomage;

	class Deck {
	public:
		Deck(const char* file, Arcomage* pGame);
		~Deck();
		int getValueFromCard(int card_num, std::string attrib);
		void update(int bricks, int gems, int beasts);
		bool clicked(int card_id);
		void discard(int card_id);
		std::string getScript(int id);
		int randomCard();
		void randomize(int current);
		bool getAdditionalTurn(int card_num);
		Card* getCard(int id)
		{
			return cards[visible[id]];
		}
		Card* getCardByID(int id)
		{
			return cards[id];
		}

		int getCardID(int id)
		{
			return visible[id];
		}

	private:
		Arcomage* game;
		Ptr<Aeon::ZipFile> archive;
		int num_cards;
		int visible[6];
		std::map<const int, Card*> cards;
		std::map<const int, std::string> scripts;
		boost::mt19937 gen;

		void loadCards();

	};
}

#endif // DECK_H_INCLUDED
