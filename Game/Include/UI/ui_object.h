/*
 * Arcomage Tribute
 *
 * File: 	ui_object.h
 * Desc: 	Basic object class, all UI Elements MUST derive from this
 *			class for the sake of polymorphism.
 *
 * Date: 	06/2007
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
#ifndef UI_OBJECT_H_INCLUDED
#define UI_OBJECT_H_INCLUDED

#ifdef __APPLE__
#include <SDL/SDL.h>

#elif __linux__
#include <SDL/SDL.h>

#else
#include <SDL.h>

#endif
#include "enumerators.h"

namespace arcomage {

	class Object {
	public:
		Object(int x, int y, Gamestate state, bool visibility);
		virtual ~Object()
		{
		}
		virtual void draw(SDL_Surface* dest) = 0;
		void setPos(int x, int y);
		void setVisibility(bool visiblity);
		void setGamestate(Gamestate state);
		bool isVisible();
		SDL_Rect getRect();
		Gamestate getAssociatedGamestate();

	protected:
		bool visible;
		int x;
		int y;
		SDL_Rect pos;
		Gamestate associatedGamestate;
	};
}
#endif // UI_OBJECT_H_INCLUDED

