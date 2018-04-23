/*
 * Arcomage Tribute
 *
 * File:	player.cpp
 * Desc: 	A basic player class.
 *
 * Date: 	10/2007
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
#include "player.h"

namespace arcomage {

	Player::Player(int towerlimit) : CPlayer(towerlimit)
	{
		name = "Player";

		pos["box_x"] = 210;
		pos["box_y"] = 483;
		pos["wall_x"] = 312;
		pos["tower_x"] = 217;
		pos["tower_y"] = pos["wall_y"] = 510;
		pos["top_x"] = 200;
		pos["text"] = 25;
		pos["box_text"] = 220;
		pos["box_text_wall"] = 320;
		Utility::getInstance()->logMessage("arcomage.log",
			std::string("[arcomage::Arcomage] New Player (")
			.append(name)
			.append(") created.").c_str());
	}

	void Player::update()
	{

		if (attributes["Tower"] <= attributes["Tower Limit"]
		&& attributes["Wall"] <= attributes["Tower Limit"]) {

			UIManager::getInstance()->moveComponent(IMAGE,
				"01_wall_player.png",
				pos["wall_x"], (int)(pos["wall_y"]-2.4*attributes["Wall"]));

			UIManager::getInstance()->setImageSize("01_wall_player.png",
				36, (int)(2.4*attributes["Wall"]));

			UIManager::getInstance()->moveComponent(IMAGE,
				"01_tower_player.png", pos["tower_x"], (int)(pos["tower_y"]-
				2.4*attributes["Tower"]));

			UIManager::getInstance()->setImageSize("01_tower_player.png",
				67, (int)(2.4*attributes["Tower"]));

			UIManager::getInstance()->moveComponent(IMAGE,
				"player_tower_top.png", pos["top_x"], (int)((pos["tower_y"]-
				2.4*attributes["Tower"])-141));
		}

		UIManager::getInstance()->setText("Player Wall",
			to_string(attributes["Wall"]));
		UIManager::getInstance()->setText("Player Tower",
			to_string(attributes["Tower"]));
		UIManager::getInstance()->setText("Player Text",
			name);

		UIManager::getInstance()->setText("Player Bricks",
			to_string(attributes["Bricks"]));
		UIManager::getInstance()->setText("Player Gems",
			to_string(attributes["Gems"]));
		UIManager::getInstance()->setText("Player Beasts",
			to_string(attributes["Beasts"]));

		UIManager::getInstance()->setText("Player Brick Modifier",
			to_string(attributes["Brick Modifier"]));
		UIManager::getInstance()->setText("Player Gem Modifier",
			to_string(attributes["Gem Modifier"]));
		UIManager::getInstance()->setText("Player Beast Modifier",
			to_string(attributes["Beast Modifier"]));
	}
}
