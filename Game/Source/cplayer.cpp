/*
 * Arcomage Tribute
 *
 * File: 	cplayer.cpp
 * Desc: 	The basic player class
 *
 * Date: 	05/2007
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

#include "cplayer.h"
#include "utility.h"

namespace arcomage {

	// -------------------------------------------------------------------------
	CPlayer::CPlayer(int towerlimit)
	{
		attributes["Tower Limit"] = towerlimit;
		this->reset(towerlimit);
		attributes["Resource Limit"] = 999;
	}

	// -------------------------------------------------------------------------
	// reset player stats
	void CPlayer::reset(int towerlimit)
	{
		attributes["Tower Limit"]   = towerlimit;
		attributes["Wall Limit"]    = towerlimit;
		this->status = game_RUNNING;
	}

	// -------------------------------------------------------------------------
	GameProgress CPlayer::endRound()
	{
		attributes["Bricks"]    +=  attributes["Brick Modifier"];
		attributes["Gems"]      +=  attributes["Gem Modifier"];
		attributes["Beasts"]    +=  attributes["Beast Modifier"];
		if (attributes["Tower"]<0)
			attributes["Tower"] = 0;
		if (attributes["Wall"]<0)
			attributes["Wall"] = 0;
		update();

		return status;
	}

	// -------------------------------------------------------------------------
	GameProgress CPlayer::getStatus()
	{
		return status;
	}
	// -------------------------------------------------------------------------
	// manually set attribute 
	void CPlayer::setAttribute(std::string dest_attrib, int value)
	{

		if (dest_attrib == "Tower") {
			if (attributes["Tower"] + value <= attributes["Tower Limit"]) {
				int diff = attributes["Tower"] + value;
				if (diff>0) {
					attributes["Tower"] += value;
				} else {
					attributes["Tower"] = 0;
					status = game_TOWER_DESTROYED;
				}

			} else {
				this->status = game_TOWER_MAX;
			}
		} else if (dest_attrib == "Wall") {
			if (attributes["Wall"] + value <= attributes["Wall Limit"]) {
				attributes["Wall"] += value;

				if(attributes["Wall"] < 0)
					attributes["Wall"] = 0;
			} else {
				this->status = game_WALL_MAX;
			}
		} else if (dest_attrib == "Damage") {
			if (attributes["Wall"]>0) {
				int diff = attributes["Wall"] - value;
				if (diff>0) {
					attributes["Wall"] -= value;
				} else {
					attributes["Wall"] -= value+diff;
					attributes["Tower"] += diff;
				}
			} else {
				int diff = attributes["Tower"] - value;
				if (diff>0) {
					attributes["Tower"] -= value;
				} else {
					attributes["Tower"] = 0;
					status = game_TOWER_DESTROYED;
				}
			}

		} else {
			attributes[dest_attrib]+=value;
			if(dest_attrib == "Brick Modifier"
				|| dest_attrib == "Beast Modifier"
				|| dest_attrib == "Gem Modifier") {
				if(attributes[dest_attrib] <= 0)
					attributes[dest_attrib] = 1;
			}

			if (attributes[dest_attrib] < 0) {
				attributes[dest_attrib] = 0;
				if (dest_attrib == "Tower") {
					status = game_TOWER_DESTROYED;
				} else if (dest_attrib == "Wall") {
					status = game_WALL_DESTROYED;
				}
			}
		}

		int limit = attributes["Resource Limit"];
		if(attributes["Bricks"] >= limit || attributes["Gems"] >= limit ||
			attributes["Beasts"] >= limit) {
			status = game_RESOURCE_MAX;
		}
	}
	// -------------------------------------------------------------------------
	int CPlayer::getAttribute(std::string attrib)
	{
		return attributes[attrib];
	}

	// -------------------------------------------------------------------------
	int CPlayer::getTowerlimit()
	{
		return attributes["Tower Limit"];
	}

	// -------------------------------------------------------------------------
	void CPlayer::setPlayerName(std::string new_name)
	{
		name = new_name;
	}

}
