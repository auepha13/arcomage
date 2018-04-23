/*
 * Arcomage Tribute
 *
 * File: ui_button.cpp
 * Desc: Button Class
 *
 * Date: 05/2007
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

#include "ui_button.h"

namespace arcomage {

	// -------------------------------------------------------------------------
	// constructor
	Button::Button( int x, int y,
		SDL_Surface* picture,
		SDL_Surface* over,
		Gamestate state_vis,
		bool visibility) : Object(x,y,state_vis,visibility)
	{
		pos.w = picture->w;
		pos.h = picture->h;
		img = picture;
		img_o = over;
		state = MOUSEOUT;
	}
	// -------------------------------------------------------------------------
	// destructor
	Button::~Button()
	{
		SDL_FreeSurface(img);
		SDL_FreeSurface(img_o);
	}
	// -------------------------------------------------------------------------
	// change button state
	void Button::setState(State pState)
	{
		state = pState;
	}
	// -------------------------------------------------------------------------
	// return the current state
	State Button::getState()
	{
		return state;
	}

	// -------------------------------------------------------------------------
	// check if the mouse is over the button
	bool Button::mouseOver()
	{
		if (Engine::getInstance()->checkMouseOver(pos)) {
			state = MOUSEOVER;
			return true;
		} else {
			state = MOUSEOUT;
			return false;
		}
	}
	// -------------------------------------------------------------------------
	// draw the button
	void Button::draw(SDL_Surface* dest)
	{
		switch (state) {
		case MOUSEOVER:
			SDL_BlitSurface(img_o, 0, dest, &pos);
			break;

		case MOUSEOUT:
			SDL_BlitSurface(img, 0, dest, &pos);
			break;
		}
	}


}
