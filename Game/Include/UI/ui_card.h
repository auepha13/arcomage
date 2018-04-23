/*
 * Arcomage Tribute
 *
 * File: ui_card.h
 * Desc: Card Image class
 *
 * Date: 06/2007
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

#ifndef UI_CARD_H_INCLUDED
#define UI_CARD_H_INCLUDED

#include "global.h"
#include "ui_object.h"

namespace arcomage {

	class CardImage : public Object {
	public:
		CardImage(SDL_Surface* picture,
			SDL_Surface* picture_mo,
			SDL_Surface* picture_d);
		~CardImage();
		void draw(SDL_Surface* dest);
		void draw(SDL_Surface* dest, int position);
		void drawAt(SDL_Surface* dest, int x, int y);
		void setDarkened(bool state);
		void setAnimated(bool val);
		SDL_Surface* getSurface();
		bool isMouseOver();


	private:
		SDL_Surface* img;
		SDL_Surface* img_mouseover;
		SDL_Surface* img_darkened;

		bool darkened;
		bool animation_in_progress;
	};
}


#endif // UI_CARD_H_INCLUDED
