/*
 * Arcomage Tribute
 *
 * File: image.h
 * Desc: Image class header
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

#ifndef UI_IMAGE_H_INCLUDED
#define UI_IMAGE_H_INCLUDED


#include "ui_object.h"

namespace arcomage {

	class Image : public Object {
	public:
		Image( int x, int y,
			SDL_Surface* picture,
			Gamestate associatedState,
			bool visible);
		~Image();
		void draw(SDL_Surface* dest);
		void setSize(int w, int h);
		SDL_Surface* getSurface();
	private:
		SDL_Surface* img;
	};
}


#endif // IMAGE_H_INCLUDED
