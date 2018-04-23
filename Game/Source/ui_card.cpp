/*
 * Arcomage Tribute
 *
 * File: ui_card.cpp
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

#include "ui_card.h"

namespace arcomage {

	// -------------------------------------------------------------------------
	// Constructor
	CardImage::CardImage(SDL_Surface* picture,
		SDL_Surface* picture_mo,
		SDL_Surface* picture_d)
		: Object(0,0,state_GAME,false)
	{
		img_darkened = picture_d;
		img_mouseover = picture_mo;
		img = picture;
		pos.w = img->w;
		pos.h = img->h;

		darkened = false;
		animation_in_progress = false;
	}

	// -------------------------------------------------------------------------
	// Destructor
	CardImage::~CardImage()
	{
		SDL_FreeSurface(img);
		SDL_FreeSurface(img_darkened);
		SDL_FreeSurface(img_mouseover);
	}

	/* set whether the card is darkened or not */
	void CardImage::setDarkened(bool state)
	{
		darkened = state;
	}

	void CardImage::setAnimated(bool val)
	{
		animation_in_progress=val;
	}
	// -------------------------------------------------------------------------
	// Draw the Image
	void CardImage::draw(SDL_Surface* dest)
	{
		if (visible) {
			SDL_BlitSurface(img, 0, dest, &pos);
		}
	}
	// -------------------------------------------------------------------------
	// Check MouseOver
	bool CardImage::isMouseOver()
	{
		return Engine::getInstance()->checkMouseOver(pos);
	}

	// -------------------------------------------------------------------------
	// Draw the Card at a specific pos
	void CardImage::drawAt(SDL_Surface* dest, int x, int y)
	{
		pos.x = x;
		pos.y = y;

		SDL_BlitSurface(img, 0, dest, &pos);
	}

	// -------------------------------------------------------------------------
	// Draw the Card
	void CardImage::draw(SDL_Surface* dest, int position)
	{
		if (visible) {
			if (!animation_in_progress) {
				pos.y=510;

				switch (position) {
				case 0:
					pos.x=10;
					break;
				case 1:
					pos.x=10+167;
					break;
				case 2:
					pos.x=10+167*2;
					break;
				case 3:
					pos.x=10+167*3;
					break;
				case 4:
					pos.x=10+167*4;
					break;
				case 5:
					pos.x=10+167*5;
					break;
				default:
					pos.x=0;
					break;
				}
				SDL_BlitSurface(img, 0, dest, &pos);

				if (!UIManager::getInstance()->isAnimationInProgress()) {
					if (Engine::getInstance()->checkMouseOver(pos))
						SDL_BlitSurface(img_mouseover, 0, dest, &pos);

					if (darkened)
						SDL_BlitSurface(img_darkened, 0, dest, &pos);
				}
			}
		}
	}
}
