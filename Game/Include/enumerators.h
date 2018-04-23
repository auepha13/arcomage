/*
 * Arcomage Tribute
 *
 * File: enumerators.h
 * Desc: Game enumeration types
 *
 * Date: 12/2008
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
#ifndef ENUMERATORS_H_INCLUDED
#define ENUMERATORS_H_INCLUDED

//------------------------------------------------------------------------------------------------------
// Constants, Enumerators..
namespace arcomage {
	enum Gamestate {
		state_INTRO,
		state_MENU,
		state_SELECT,
		state_TUORIAL,
		state_OPTIONS,
		state_CREDITS,
		state_LOAD,
		state_GAME,
		state_EXIT,
		state_END,
		state_PAUSE
	};

	enum GameProgress {
		game_RUNNING,
		game_UNUSED_WHATEVER_LOL,
		game_TOWER_MAX,
		game_TOWER_DESTROYED,
		game_WALL_MAX,
		game_WALL_DESTROYED,
		game_RESOURCE_MAX
	};

	enum State {
		MOUSEOVER,
		MOUSEOUT
	};

	enum textquality {
		solid,
		shaded,
		blended
	};

	enum Component {
		BUTTON,
		IMAGE,
		TEXT
	};
}

#endif // ENUMERATORS_H_INCLUDED
