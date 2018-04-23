/*
 * Arcomage Tribute
 *
 * File: cplayer.h
 * Desc: abstract player class header
 *
 * Date: 05/2007
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

#ifndef CPLAYER_H_INCLUDED
#define CPLAYER_H_INCLUDED

#include <string>
#include <map>
#include "enumerators.h"

namespace arcomage {

	class CPlayer {
	public:
		CPlayer(int towerlimit);
		virtual ~CPlayer()
		{
		};
		bool loaded();

		void setPlayerName(std::string new_name);

		void playCards();
		GameProgress endRound();
		GameProgress getStatus();
		void discard();
		virtual void update() = 0;

		void setAttribute(std::string dest_attrib, int value);
		int getAttribute(std::string attrib);
		int getTowerlimit();

		void reset(int towerlimit);

	protected:
		/* Player specific text */
		std::string name;
		GameProgress status;

		/* containers */
		std::map<const std::string, int> attributes;
		std::map<const std::string, int> pos;
	};
}

#endif // CPLAYER_H_INCLUDED
