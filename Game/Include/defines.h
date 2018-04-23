/*
 * Arcomage Tribute
 *
 * File: defines.h
 * Desc: Game definitions, includes cross platform paths
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

#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

//------------------------------------------------------------------------------------------------------
// Game Frame Rate
#define FRAMES_PER_SECOND 30
#define BOOST_FILESYSTEM_VERSION 2

//------------------------------------------------------------------------------------------------------
// General Defines to enhance readability
#define method(class, name) {#name, &class::name}

//------------------------------------------------------------------------------------------------------

// Used to wrap poorly designed legacy code (macros for strings?!)...
#include <boost/filesystem.hpp>

#define BOOSTPATH(parm) boost::filesystem::path(parm).string().c_str()

#define CONFIG BOOSTPATH("data/config.xml")

// Fonts
#define KINGTHINGS BOOSTPATH("data/ttf/Kingthings_Exeter.ttf")
#define ARCHTURA BOOSTPATH("data/ttf/archtura.ttf")

// Paths
#define CARDPATH BOOSTPATH("data/images/card/")
#define DECK_FILE BOOSTPATH("data/decks/deck.xml")
#define DECK_PATH BOOSTPATH("data/decks/")
#define TEMPLATE_P BOOSTPATH("data/decks/")
#define GFX_P BOOSTPATH("data/images/")
#define BUTTON_P BOOSTPATH("data/images/interface/")
#define MUSIC_P BOOSTPATH("data/music/")
#define MUSIC_FILE BOOSTPATH("data/music/music.xml")
#define XML_PATH BOOSTPATH("data/interface/")
#define SCRIPT_PATH BOOSTPATH("data/scripts/")
#define SCRIPT_PATH_C BOOSTPATH("data/scripts/card")
#define AI_SCRIPT BOOSTPATH("data/scripts/ai/enemy_turn.lua")
#endif // DEFINES_H_INCLUDED
