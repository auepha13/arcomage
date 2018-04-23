/*
 * Arcomage Tribute
 *
 * File:	scriptbind.cpp
 * Desc: 	Script Bindings to allow game scripting using LUA.
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
#include "scriptbind.h"

namespace arcomage {

	// -------------------------------------------------------------------------
	// Constructor, requires 3 pointers to player, deck, enemy, else assertion fail
	ScriptBind::ScriptBind(lua_State* L)
	{
		assert(lua_gettop( L ) == 3);
		player = (Player*)lua_touserdata(L, 1);
		deck = (Deck*)lua_touserdata(L, 2);
		enemy = (Enemy*)lua_touserdata(L, 3);
	}

	// -------------------------------------------------------------------------
	ScriptBind::~ScriptBind()
	{

	}

	//--------------------------------------------------------------------------
	// Script Functions

	//--------------------------------------------------------------------------
	// Get the current towerlimit
	int ScriptBind::getTowerlimit( lua_State* L )
	{
		if (lua_gettop( L ) == 0) {
			lua_pushnumber(L, this->player->getTowerlimit());
			return 1;
		} else {
			return -1;
		}
	}

	//--------------------------------------------------------------------------
	int ScriptBind::setResourceLimit( lua_State* L )
	{
		if (lua_gettop( L ) == 1) {
			int number = (int)luaL_checknumber(L, 1);

			this->enemy->setAttribute("Resource Limit",
				-999+number);
			this->player->setAttribute("Resource Limit",
				-999+number);
			return 0;
		} else {
			return -1;
		}
	}

	//--------------------------------------------------------------------------
	// set an attribute of the player
	int ScriptBind::setPlayerAttribute( lua_State* L )
	{
		if (lua_gettop( L ) == 2) {
			this->player->setAttribute(lua_tostring(L, 1),
				(int)luaL_checknumber(L, 2));
			return 0;
		} else {
			return -1;
		}
	}


	//--------------------------------------------------------------------------
	// Resets an Enemy Attribute to the given number
	int ScriptBind::resetEnemyAttribute( lua_State* L )
	{
		if (lua_gettop( L ) == 2) {
			this->enemy->setAttribute(lua_tostring(L,
				1), -this->enemy->getAttribute(lua_tostring(L, 1)));
			this->enemy->setAttribute(lua_tostring(L,
				1), (int)luaL_checknumber(L, 2) - 1 );
			return 0;
		} else {
			return -1;
		}
	}
	//--------------------------------------------------------------------------
	// Resets a Player Attribute to the given number
	int ScriptBind::resetPlayerAttribute( lua_State* L )
	{
		if (lua_gettop( L ) == 2) {
			this->player->setAttribute(lua_tostring(L,
				1), -this->player->getAttribute(lua_tostring(L, 1)));
			this->player->setAttribute(lua_tostring(L,
				1), (int)luaL_checknumber(L, 2) - 1);
			return 0;
		} else {
			return -1;
		}
	}

	//--------------------------------------------------------------------------
	// set an attribute of the enemy
	int ScriptBind::setEnemyAttribute( lua_State* L )
	{
		if (lua_gettop( L ) == 2) {
			this->enemy->setAttribute(lua_tostring(L, 1),
				(int)luaL_checknumber(L, 2));
			return 0;
		} else {
			return -1;
		}
	}
	//--------------------------------------------------------------------------
	// returns an attribute of the enemy
	int ScriptBind::getEnemyAttribute( lua_State* L )
	{
		if (lua_gettop( L ) == 1) {
			lua_pushnumber(L, this->enemy->getAttribute(lua_tostring(L, 1)));
			return 1;
		} else {
			return -1;
		}
	}

	//--------------------------------------------------------------------------
	// get an attribute from a card
	int ScriptBind::getValueFromCard( lua_State* L )
	{
		if (lua_gettop( L ) == 2) {
			lua_pushnumber(L, this->deck->getValueFromCard(
				(int)luaL_checknumber(L, 1),
				lua_tostring(L, 2))
				);
			return 1;
		} else {
			return -1;
		}
	}

	//--------------------------------------------------------------------------
	// additional turn?
	int ScriptBind::getAdditionalTurn( lua_State* L )
	{
		if (lua_gettop( L ) == 1) {
			lua_pushboolean(L,
				this->deck->getAdditionalTurn((int)luaL_checknumber(L, 1)));
			return 1;
		} else {
			return -1;
		}
	}

	//--------------------------------------------------------------------------
	// animation in progress?
	int ScriptBind::getAnimationInProgress( lua_State* L )
	{
		if (lua_gettop( L ) == 0) {
			lua_pushboolean(L,
				UIManager::getInstance()->isAnimationInProgress());
			return 1;
		} else {
			return -1;
		}
	}

	//--------------------------------------------------------------------------
	// set an attribute of both the player and enemy
	int ScriptBind::setAttribute( lua_State* L )
	{
		if (lua_gettop( L ) == 2) {
			this->player->setAttribute(lua_tostring(L, 1),
				(int)luaL_checknumber(L, 2));
			this->enemy->setAttribute(lua_tostring(L, 1),
				(int)luaL_checknumber(L, 2));
			return 0;
		} else {
			return -1;
		}
	}

	//--------------------------------------------------------------------------
	// returns an attribute of the current player
	int ScriptBind::getPlayerAttribute( lua_State* L )
	{
		if (lua_gettop( L ) == 1) {
			lua_pushnumber(L, this->player->getAttribute(lua_tostring(L,
				1)));
			return 1;
		} else {
			return -1;
		}
	}

	//--------------------------------------------------------------------------
	// Randomize a card
	int ScriptBind::selectRandomCard( lua_State* L )
	{
		if (lua_gettop( L ) == 0) {
			lua_pushnumber(L, this->deck->randomCard());
			return 1;
		} else {
			return -1;
		}
	}

	//--------------------------------------------------------------------------
	// CardAnimation
	int ScriptBind::animateCard( lua_State* L )
	{
		if (lua_gettop( L ) == 2) {
			UIManager::getInstance()->animateCard((int)luaL_checknumber(L,
				1),
				(double)luaL_checknumber(L, 2));
			return 0;
		} else {
			return -1;
		}
	}

	//--------------------------------------------------------------------------
	int ScriptBind::wait( lua_State* L )
	{
		if (lua_gettop( L ) == 1) {
			SDL_Delay((int)luaL_checknumber(L, 1));
			return 0;
		} else {
			return -1;
		}
	}

	//--------------------------------------------------------------------------
	// play a sound effect
	int ScriptBind::playSound( lua_State* L )
	{
		if (lua_gettop( L ) == 1) {
			Engine::getInstance()->playSound(lua_tostring(L, 1));
			return 1;
		} else {
			return -1;
		}
	}

	//--------------------------------------------------------------------------
	// saves a message to the arcomage log file (with a prefix to indicate the script message)
	int ScriptBind::saveLogMessage( lua_State* L )
	{
		if (lua_gettop( L ) == 1) {
			Utility::getInstance()->logMessage("arcomage.log",
				std::string("[arcomage::Script] (Script Message) ")
				.append(lua_tostring( L, 1)).c_str());
			return 0;
		} else {
			return -1;
		}
	}
}
