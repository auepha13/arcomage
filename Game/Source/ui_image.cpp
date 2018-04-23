/*
 * Arcomage Tribute
 *
 * File: ui_image.cpp
 * Desc: Image class
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

#include "ui_image.h"

namespace arcomage {

	// -------------------------------------------------------------------------
	// Constructor
	Image::Image(int x, int y,
		SDL_Surface* picture,
		Gamestate state,
		bool visible)
		: Object(x,y,state,visible)
	{
		pos.w = picture->w;
		pos.h = picture->h;
		img = picture;
	}

	// -------------------------------------------------------------------------
	// Destructor
	Image::~Image()
	{
		SDL_FreeSurface(img);
	}

	// -------------------------------------------------------------------------
	// Set Size
	void Image::setSize(int w, int h)
	{
		img->w = w;
		img->h = h;
	}

	// -------------------------------------------------------------------------
	// Return Image
	SDL_Surface* Image::getSurface()
	{
		return img;
	}

	// -------------------------------------------------------------------------
	// Draw the Image
	void Image::draw(SDL_Surface* dest)
	{
		if (visible)
			SDL_BlitSurface(img, 0, dest, &pos);
	}
}
