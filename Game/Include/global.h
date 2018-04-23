/*
 * Arcomage Tribute
 *
 * File: global.h
 * Desc: Main Include file handles all importing includes
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
#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

//------------------------------------------------------------------------------------------------------
// Definitions
#include "defines.h"

//------------------------------------------------------------------------------------------------------
// SDL Includes
#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#elif __linux__
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#else
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#endif

//------------------------------------------------------------------------------------------------------
// System Includes
#include <iostream>
#include <vector>
#include <sstream>
#include <string.h>
#include <vector>
#include <map>
#include <time.h>

#include "txml/tinyxml.h"
#include "enumerators.h"
#include "version.h"

//------------------------------------------------------------------------------------------------------
// Includes
#include "ui_manager.h"
#include "utility.h"
#include "singleton.h"
#include "config.h"
#include "engine.h"
#include "deck.h"
#include "player.h"
#include "enemy.h"
#include "script.h"
#include "timer.h"
#include "deckpreview.h"

static Uint32 next_time;

#endif // GLOBAL_H_INCLUDED
