/*
 * Arcomage Tribute
 *
 * File: card.h
 * Desc: Card class header
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

#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include "ArcomageForward.h"
#include "AeonCore.h"

#include <SDL.h>
#include <SDL_ttf.h>

namespace arcomage {

	class Card {
	public:
		Card(int pId, Ptr<Aeon::ZipFile> archive);
		~Card();
		void init(int pID);
		void draw(SDL_Surface* dest, int pos);
		SDL_Rect getRect();
		bool getDeckState();
		int getValue(std::string attribute);
		bool additionalTurn();
		bool discardCard();
		bool checkRequirements(int current_bricks,
			int current_gems,
			int current_beasts);
		void setDarkened(bool state);
		bool isDarkened();
		std::string getName();
		std::string getScript();

	private:
		bool mouseover;
		bool ondeck;
		bool darkened;

		SDL_Surface* buildImage(Ptr<Aeon::ZipFile> arch);
		SDL_Surface* image;

		// card data
		std::map<const std::string, int> data;

		// boolean
		bool addturn;
		bool discard;

		// texts
		std::string deckname;
		std::string name;
		std::string filename;
		std::string script;
		std::string descripton;

		std::vector<std::string> description_vec;
		
		SDL_Rect card_rect;
		SDL_Rect card_picture_rect;
		SDL_Rect mouseover_rect;

		TTF_Font* font_name;
		TTF_Font* font_desc;

	};
}

#endif // CARD_H_INCLUDED
