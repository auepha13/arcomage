/*
 * Arcomage Tribute
 *
 * File: script.h
 * Desc: Wrapper for the Script Bindings
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

#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED


#include "scriptbind.h"
#include "luna.h"
#include "cplayer.h"
#include "player.h"
#include "enemy.h"
namespace arcomage {

	class Script {
	public:
		Script(Deck* p_deck, Player* p_player, Enemy* p_enemy);
		~Script();

		void execute(const char* file);
		void executeFromMemory(const char* data);
		inline operator lua_State*()
		{
			return g_LuaInstance;
		}

		void setPlayers(CPlayer* player, CPlayer* enemy);

	private:
		lua_State* g_LuaInstance;
		void report_errors(lua_State* L, const int status);
		int execute_program(lua_State* L);
		Deck* deck;
		CPlayer* player;
		CPlayer* enemy;
	};
}

#endif // SCRIPT_H_INCLUDED
