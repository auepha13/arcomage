/*
 * Arcomage Tribute
 *
 * File: game.h
 * Desc: Game class
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

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "global.h"
#include "defines.h"
#include "AnimationListener.h"

#include <boost/filesystem.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

namespace arcomage {
	class Deck;
	class Player;
	class Enemy;
	class Script;
	class Timer;
	class DeckPreview;
	class Card;
	class CPlayer;

	class Arcomage : public AnimationListener {

		// -------------------------------------------------------------------------
		// Public
	public:
		// Methods
		Arcomage();
		~Arcomage();
		bool quit();
		void run();

		void updateProgress(std::string progress, int percent);
		void update();
		Gamestate getGamestate();

		// Implementing AnimationListener
		void animationStarted();
		void notifyAnimationIdle();
		void animationFinished();
		Gamestate getState()
		{
			return current_state;
		}

		// -------------------------------------------------------------------------
		// Private
	private:
		// Fps specific
		Uint32 last;
		boost::mt19937 gen;

		int frame;
		int fps;
		double timeSinceLastFrame;
		double time;
		bool disp_switch;
		std::string selected_deck, previous_deck;
		std::vector<DeckPreview*> deck_list;
		Deck* deck;
		Card* lastCard;
		int lastCardID;
		int selected_index;
		int selection_offset;
		double waitTime;
		bool doWait;
		bool hasToDiscard;

		// Attributes
		Gamestate current_state;
		GameProgress status;
		void checkStatus(bool isPlayer);

		SDL_Surface* gamescreen;
		std::map<const Gamestate, bool> init;
		SDL_Rect centerPoint;

		// Methods
		void setGamestate(Gamestate state);
		void stateMusicManager(Gamestate state);
		void handleEvents();


		// gamestates
		void gs_startup();
		void gs_menu();
		void gs_select();
		void gs_credits();
		void gs_loading();
		void gs_game();
		void gs_pause();
		void gs_game_over();
		void gs_options();

		// logic
		void apply(int card);
		void discard(int card);
		void enemy_turn();
		void setSelectionIndex(int index);
		void applyChanges(CPlayer* current, CPlayer* other);

		// game specific stuff
		int towerlimit;
		std::string progress;
		bool quit_game;
		bool discardAnimation;
		bool checkCard(int id);

		// Assoc
		// Deck* deck;
		Player* player;
		Enemy* enemy;
		Script* script;
	};
}

#endif // GAME_H_INCLUDED
