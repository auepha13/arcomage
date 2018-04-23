/*
 * Arcomage Tribute
 *
 * File:	script.cpp
 * Desc: 	Script class, providing an interface to the Arcomage Script
 *			Bindings (LUA).
 *
 * Date: 	12/2008
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
#include "script.h"

namespace arcomage {

	// the class name we use
	const char ScriptBind::className[] = "Arcomage";

	// registered methods
	Luna<ScriptBind>::RegType ScriptBind::methods[] = {
			method(ScriptBind, setPlayerAttribute),
			method(ScriptBind, setEnemyAttribute),
			method(ScriptBind, getEnemyAttribute),
			method(ScriptBind, getPlayerAttribute),
			method(ScriptBind, getValueFromCard),
			method(ScriptBind, setAttribute),
			method(ScriptBind, getTowerlimit),
			method(ScriptBind, selectRandomCard),
			method(ScriptBind, animateCard),
			method(ScriptBind, playSound),
			method(ScriptBind, getAdditionalTurn),
			method(ScriptBind, getAnimationInProgress),
			method(ScriptBind, wait),
			method(ScriptBind, saveLogMessage),
			method(ScriptBind, setResourceLimit),
			method(ScriptBind, resetEnemyAttribute),
			method(ScriptBind, resetPlayerAttribute),
			{0,0}
		};

	// -------------------------------------------------------------------------
	Script::Script(Deck* p_deck, Player* p_player, Enemy* p_enemy)
	{
		g_LuaInstance = lua_open();
		luaopen_base( g_LuaInstance );

		this->player = p_player;
		this->deck = p_deck;
		this->enemy = p_enemy;

		Luna<ScriptBind>::Register( g_LuaInstance );

		lua_pushlightuserdata(g_LuaInstance, (void*)player);
		lua_setglobal(g_LuaInstance, "player");

		lua_pushlightuserdata(g_LuaInstance, (void*)deck);
		lua_setglobal(g_LuaInstance, "deck");

		lua_pushlightuserdata(g_LuaInstance, (void*)enemy);
		lua_setglobal(g_LuaInstance, "enemy");

		// Feeble attempt to hide the object binding from the user.
		luaL_dostring(g_LuaInstance,
			"arcomage = Arcomage(player, deck, enemy)");

		this->execute(std::string(SCRIPT_PATH).append("startup.lua").
			c_str());

	}

	// -------------------------------------------------------------------------
	Script::~Script()
	{
		lua_close(g_LuaInstance);
	}

	// -------------------------------------------------------------------------
	void Script::execute(const char* file)
	{
		int s = luaL_loadfile(g_LuaInstance, file);
		s = execute_program(g_LuaInstance);
		report_errors(g_LuaInstance, s);

	}

	// -------------------------------------------------------------------------
	void Script::executeFromMemory(const char* data)
	{
		int s = luaL_dostring(g_LuaInstance, data);
		report_errors(g_LuaInstance, s);

	}
	// -------------------------------------------------------------------------
	void Script::setPlayers(CPlayer* player, CPlayer* enemy)
	{
		this->player = player;
		this->enemy = enemy;

		lua_pushlightuserdata(g_LuaInstance, (void*)player);
		lua_setglobal(g_LuaInstance, "player");

		lua_pushlightuserdata(g_LuaInstance, (void*)deck);
		lua_setglobal(g_LuaInstance, "deck");

		lua_pushlightuserdata(g_LuaInstance, (void*)enemy);
		lua_setglobal(g_LuaInstance, "enemy");

		luaL_dostring(g_LuaInstance,
			"arcomage = Arcomage(player, deck, enemy)");
	}

	// -------------------------------------------------------------------------
	int Script::execute_program(lua_State* L)
	{
		return lua_pcall(L, 0, LUA_MULTRET, 0);
	}

	// -------------------------------------------------------------------------
	void Script::report_errors(lua_State* L, const int status)
	{
		if (status!=0) {
			Utility::getInstance()->logMessage("script.log",
				std::string("[arcomage::Script] ")
				.append(lua_tostring(L, -1)).c_str());
			lua_pop(L, 1); // remove error message
		}
	}

}
