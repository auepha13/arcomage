/*
 * Arcomage Tribute
 *
 * File: scriptbind.h
 * Desc: LUA Bindings
 *
 * Date: 07/2008
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

#ifndef SCRIPTBIND_H_INCLUDED
#define SCRIPTBIND_H_INCLUDED

#include "global.h"
#include "luna.h"
#include "utility.h"

namespace arcomage {
	class Deck;
	class Player;
	class Enemy;
	class CPlayer;

	class ScriptBind {
	public:
		ScriptBind(lua_State* L);
		~ScriptBind();

		static const char className[];
		static Luna<ScriptBind>::RegType methods[];
		void setData(lua_State* L,
			Deck* p_deck,
			Player* p_player,
			Enemy* p_enemy);

		int getPlayerAttribute( lua_State* L );
		int setPlayerAttribute( lua_State* L );
		int setEnemyAttribute( lua_State* L );
		int getAdditionalTurn( lua_State* L );
		int getEnemyAttribute( lua_State* L );
		int setAttribute( lua_State* L );
		int getTowerlimit( lua_State* L );
		int saveLogMessage( lua_State* L );
		int selectRandomCard( lua_State* L );
		int getValueFromCard( lua_State* L );
		int animateCard( lua_State* L );
		int playSound( lua_State* L );
		int getAnimationInProgress( lua_State* L );
		int wait( lua_State* L );
		int setResourceLimit( lua_State* L );
		int resetEnemyAttribute( lua_State* L );
		int resetPlayerAttribute( lua_State* L );
	private:
		Deck* deck;
		Player* player;
		Enemy* enemy;
	};
}

#endif // SCRIPTBIND_H_INCLUDED
