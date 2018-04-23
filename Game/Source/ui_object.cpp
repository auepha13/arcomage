/*
 * Arcomage Tribute
 *
 * File: 	ui_object.cpp
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
#include "ui_object.h"

namespace arcomage {

	// -------------------------------------------------------------------------
	// Constructor
	Object::Object(int x, int y, Gamestate state, bool visibility)
	{
		this->x = x;
		this->y = y;
		pos.x = x;
		pos.y = y;
		associatedGamestate = state;
		visible = visibility;
	}
	// -------------------------------------------------------------------------
	// Move the Object
	void Object::setPos(int x, int y)
	{
		pos.x = x;
		pos.y = y;
	}

	// -------------------------------------------------------------------------
	// Set Visibility
	void Object::setVisibility(bool visiblity)
	{
		visible = visiblity;
	}

	// -------------------------------------------------------------------------
	// Change Gamestate
	void Object::setGamestate(Gamestate state)
	{
		associatedGamestate = state;
	}

	// -------------------------------------------------------------------------
	// Returns whether the Object is visible or not
	bool Object::isVisible()
	{
		return visible;
	}

	// -------------------------------------------------------------------------
	// Returns the Rectangle of the Object
	SDL_Rect Object::getRect()
	{
		return pos;
	}

	// -------------------------------------------------------------------------
	// Returns the associated Gamestate
	Gamestate Object::getAssociatedGamestate()
	{
		return associatedGamestate;
	}
}

