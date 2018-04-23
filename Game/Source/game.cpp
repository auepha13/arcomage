/*
 * Arcomage Tribute
 *
 * File:	game.cpp
 * Desc: 	The Game class, containing the game logic. Manages
 *			Game States and handles user input accordingly.
 *
 * Date: 	05/2007
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
#include "game.h"

namespace arcomage {
	// -------------------------------------------------------------------------
	Arcomage::Arcomage()
		: deck(0),
		timeSinceLastFrame(0.0),
		fps(0),
		time(0.0),
		last(0),
		lastCard(0),
		waitTime(0.5),
		discardAnimation(false),
		gen(static_cast<unsigned>(std::time(0)) ^ 0xDEADBEEF),
		hasToDiscard(false),
		selection_offset(0)
	{
		quit_game = false;

		// Initialize Engine
		Engine::getInstance()->init(CONFIG);
		Engine::getInstance()->setGame(this);

		if (Engine::getInstance()->getIntroEnabled()) {
			this->setGamestate(state_INTRO);
		} else {
			this->setGamestate(state_MENU);
		}

		centerPoint = Engine::getInstance()->getCenter();
		towerlimit = 100;
		// deck = 0;

		next_time = SDL_GetTicks() + FRAMES_PER_SECOND;

		// Preload Game Over screen
		UIManager::getInstance()->loadFromXML("game_over.xml", state_END);
		Utility::getInstance()->logMessage("arcomage.log",
			std::string("[arcomage::Arcomage] Game Initialized.").c_str());
		UIManager::getInstance()->setAnimationProgress(false);
		UIManager::getInstance()->setEnemyAnimationProgress(false);
		UIManager::getInstance()->setAnimationCallback(this);
		disp_switch = false;
		previous_deck = "";
		selected_deck = "Default.deck";
		selected_index = 0;
	}

	// -------------------------------------------------------------------------
	// Set Gamestate
	void Arcomage::setGamestate(Gamestate state)
	{
		this->stateMusicManager(state);
		current_state = state;
	}
	// -------------------------------------------------------------------------
	// Get Gamestate
	Gamestate Arcomage::getGamestate()
	{
		return current_state;
	}

	// -------------------------------------------------------------------------
	// Change Music when a state change happens
	void Arcomage::stateMusicManager(Gamestate state)
	{
		if (state == state_MENU && current_state != state_SELECT) {
			Engine::getInstance()->stopMusic();
			Engine::getInstance()->playMusic("Title");
		} else if (state == state_CREDITS) {
			Engine::getInstance()->stopMusic();
			Engine::getInstance()->playMusic("Credits");
		} else if (state == state_GAME && current_state != state_PAUSE) {
			boost::variate_generator<boost::mt19937&,
				boost::uniform_int<> > die(gen, boost::uniform_int<>(1, 2));
			Engine::getInstance()->stopMusic();
			Engine::getInstance()->playMusic(std::string("Game ").
				append(to_string(die())));
		}
	}
	// -------------------------------------------------------------------------
	// Quit the game?
	bool Arcomage::quit()
	{
		if(!init[state_MENU])
			return false;
		else
			return quit_game;
	}

	// -------------------------------------------------------------------------
	// -------------------------------------------------------------------------
	// Game States
	// -------------------------------------------------------------------------
	// Intro
	void Arcomage::gs_startup()
	{
		if (!init[state_INTRO]) {
			UIManager::getInstance()->loadFromXML("startup.xml",
				state_INTRO);
			init[state_INTRO] = true;
			Engine::getInstance()->render(timeSinceLastFrame);
			SDL_Delay(2000);
			this->setGamestate(state_MENU);
		}
	}

	// -------------------------------------------------------------------------
	// Main Menu
	void Arcomage::gs_menu()
	{
		if (!init[state_MENU]) {
			UIManager::getInstance()->loadFromXML("menu_main.xml",
				state_MENU);
			UIManager::getInstance()->setText("Version Text",
				std::string("Arcomage Tribute ").
				append(AutoVersion::FULLVERSION_STRING));

			init[state_MENU] = true;
		}
	}
	// -------------------------------------------------------------------------
	// Credits
	void Arcomage::gs_credits()
	{
		if (!init[state_CREDITS]) {
			UIManager::getInstance()->loadFromXML("credits.xml",
				state_CREDITS);
			init[state_CREDITS] = true;
		}
	}
	// -------------------------------------------------------------------------
	// Select
	void Arcomage::gs_select()
	{
		if (!init[state_SELECT]) {
			UIManager::getInstance()->loadFromXML("menu_select.xml",
				state_SELECT);

			boost::filesystem::path d_path( boost::filesystem::initial_path<
				boost::filesystem::path>() );
			d_path = boost::filesystem::system_complete( boost::filesystem::
				path( DECK_PATH ) );

			boost::filesystem::directory_iterator end_itr; // default construction yields past-the-end

			if(!boost::filesystem::exists(d_path))
				Utility::getInstance()->
					exitError(std::string("Failed to access directory: ").
					append(d_path.directory_string()).c_str());

			for (boost::filesystem::directory_iterator itr( d_path );
				itr != end_itr;
				++itr) {
				if(Utility::getInstance()->getFileExtension(itr->leaf()) ==
					".deck") {
					Ptr<Aeon::ZipFile> ptr =
						Aeon::AeonCompress::createZipFile(boost::filesystem::
						path(d_path/itr->leaf()).string(),
						Aeon::ZipMode::ZIP_CACHE_NONE);
					deck_list.push_back(new DeckPreview(ptr, itr->leaf()));

				}
			}

			int ctr = 0;
			std::vector<DeckPreview*>::const_iterator it;

			for (it = deck_list.begin();
				it != deck_list.end();
				++it) {
				ctr++;
				if (ctr <= 5) {
					UIManager::getInstance()->
						setText(std::string("Selection Line ").
						append(to_string(ctr)),
						deck_list[ctr-1]->getMetaData("Filename"));
				}
			}

			selection_offset = 0;
			this->setSelectionIndex(0);

			init[state_SELECT] = true;
		}
	}

	// -------------------------------------------------------------------------
	void Arcomage::setSelectionIndex(int index)
	{
		if(selected_deck != "") {
			previous_deck = selected_deck;
		}

		int actual_index = index+selection_offset;
		UIManager::getInstance()->setText("Number of Cards",
			std::string("Cards: ").append(deck_list[actual_index]->
			getMetaData("Cards")));

		UIManager::getInstance()->setText("Deck Metadata Name",
			deck_list[actual_index]->getMetaData("Name"));
		UIManager::getInstance()->setText("Deck Metadata Author",
			deck_list[actual_index]->getMetaData("Author"));
		std::stringstream sstr;
		sstr << deck_list[actual_index]->getMetaData("Version")
			<< "(" << deck_list[actual_index]->getMetaData("Date") << ")";

		UIManager::getInstance()->setText("Deck Metadata VersionDate",
			sstr.str());

		UIManager::getInstance()->moveComponent(IMAGE, "selection_bar.png",
			centerPoint.x+32, centerPoint.y-12+(index*24));

		selected_deck = deck_list[actual_index]->getMetaData("Filename");

		int ctr = selection_offset;
		for (std::vector<DeckPreview*>::const_iterator it = deck_list.
			begin();
			it != deck_list.end();
			++it) {
			ctr++;
			if (ctr <= selection_offset+5) {
				UIManager::getInstance()->
					setText(std::string("Selection Line ").
					append(to_string(ctr-selection_offset)),
					deck_list[ctr-1]->getMetaData("Filename"));
			}
		}
	}

	// -------------------------------------------------------------------------
	// Select
	void Arcomage::gs_loading()
	{
		if (!init[state_LOAD]) {
			UIManager::getInstance()->loadFromXML("loading.xml", state_LOAD);

			Utility::getInstance()->logMessage("arcomage.log",
				"[arcomage::Arcomage] Starting new game");

			progress = "Loading...";
			UIManager::getInstance()->setImageSize("progress.png", 0, 137);
			update();
			if(deck)
				delete deck;

			deck = new Deck(selected_deck.c_str(), this);

			std::string file = "";

			UIManager::getInstance()->setImageSize("progress.png", 889, 137);
			progress = "Creating Players...";
			update();

			player = new Player(towerlimit);
			enemy = new Enemy(towerlimit);

			player->setPlayerName("Player ***");
			enemy->setPlayerName("Enemy");

			UIManager::getInstance()->setPlayerTurn(true);

			gs_game();
			init[state_LOAD] = true;

			script = new Script(deck, player, enemy);

			this->setGamestate(state_GAME);

			player->update();
			enemy->update();
			deck->update(player->getAttribute("Bricks"),
				player->getAttribute("Gems"),
				player->getAttribute("Beasts"));
		}

		// We want the player to have always the first turn after the loading screen.
		UIManager::getInstance()->setPlayerTurn(true);
	}
	// -------------------------------------------------------------------------
	void Arcomage::update()
	{
		UIManager::getInstance()->setText("Info", progress);
		Engine::getInstance()->render(timeSinceLastFrame);
	}
	// -------------------------------------------------------------------------
	void Arcomage::updateProgress(std::string progress, int percent)
	{
		this->progress = progress;
		UIManager::getInstance()->setImageSize("progress.png",
			((889*percent)/100), 137);
	}

	// -------------------------------------------------------------------------
	// Game
	void Arcomage::gs_game()
	{
		if (!init[state_GAME]) {
			UIManager::getInstance()->loadFromXML("game.xml", state_GAME);
			UIManager::getInstance()->
				setImageVisibility("discard_overlay.png", false);
			UIManager::getInstance()->setTextVisibility("DiscardTextOverlay",
				false);
			player->update();
			deck->update(player->getAttribute("Bricks"),
				player->getAttribute("Gems"),
				player->getAttribute("Beasts"));
			init[state_GAME] = true;
		} else {
			if (!UIManager::getInstance()->getPlayerTurn()
				&& !UIManager::getInstance()->isAnimationInProgress()) {
				this->enemy_turn();
				disp_switch = true;
			}

			if (disp_switch && UIManager::getInstance()->getPlayerTurn() &&
				!UIManager::getInstance()->isAnimationInProgress()) {
				player->setPlayerName("Player ***");
				enemy->setPlayerName("Enemy");
				enemy->update();
				player->update();
				disp_switch = false;
			}
		}
	}
	// -------------------------------------------------------------------------
	// Pause
	void Arcomage::gs_pause()
	{
		if (!init[state_PAUSE]) {
			UIManager::getInstance()->loadFromXML("menu_pause.xml",
				state_PAUSE);
			init[state_PAUSE] = true;
		}
	}

	// -------------------------------------------------------------------------
	// Game Over
	void Arcomage::gs_game_over()
	{
		if (!init[state_END]) {
			// UIManager::getInstance()->loadFromXML("game_over.xml",state_END);
			init[state_END] = true;
		}
	}

	// -------------------------------------------------------------------------
	// Options
	void Arcomage::gs_options()
	{
	}

	// -------------------------------------------------------------------------
	// -------------------------------------------------------------------------
	// Game Logic

	// -------------------------------------------------------------------------
	// Apply Click
	void Arcomage::apply(int card)
	{
		// Deck specific changes
		player->update();

		if (deck->clicked(card)) {
			// The players' turn
			player->setPlayerName("Player ***");
			enemy->setPlayerName("Enemy");

			std::string type[] = {"Bricks", "Gems", "Beasts" };
			player->setAttribute(type[deck->getValueFromCard(card, "Type")],
				-deck->getValueFromCard(card, "Requirements"));
			deck->update(player->getAttribute("Bricks"),
				player->getAttribute("Gems"),
				player->getAttribute("Beasts"));

			player->update();

			UIManager::getInstance()->setPlayerTurn(true);
			Engine::getInstance()->playSound("card");
			UIManager::getInstance()->animateCard(card, 0.5);
			lastCard = deck->getCard(card);
			script->setPlayers(player, enemy);
		}
	}

	// -------------------------------------------------------------------------
	bool Arcomage::checkCard(int id)
	{
		std::string type[] = {"Bricks", "Gems", "Beasts" };
		return enemy->getAttribute(type[deck->getValueFromCard(id, "Type")])
			>= deck->getValueFromCard(id, "Requirements");
	}

	// -------------------------------------------------------------------------
	// Enemy Turn
	void Arcomage::enemy_turn()
	{
		if(current_state != state_END) {
			player->setPlayerName("Player");
			enemy->setPlayerName("Enemy ***");
			enemy->update();
			player->update();

			int random;

			// The Enemy AI: Select random card :)
			do {
				random = deck->randomCard();
			} while(!checkCard(random));

			lastCardID = random;

			if(!hasToDiscard) {
				std::string type[] = {"Bricks", "Gems", "Beasts" };
				enemy->setAttribute(type[deck->getValueFromCard(random,
					"Type")],
					-deck->getValueFromCard(random, "Requirements"));

				deck->update(enemy->getAttribute("Bricks"),
					enemy->getAttribute("Gems"),
					enemy->getAttribute("Beasts"));

				enemy->update();

				Engine::getInstance()->playSound("card");

				script->setPlayers(enemy, player);

				UIManager::getInstance()->animateCard(random, 0.5);
			} else {
				UIManager::getInstance()->animateCard(random, 0.35, true);
			}
			//script->execute(AI_SCRIPT);
		}
	}

	// -------------------------------------------------------------------------
	// Player discards a card
	void Arcomage::discard(int card)
	{
		// Engine::getInstance()->playSound("card");
		discardAnimation = true;
		UIManager::getInstance()->setPlayerTurn(true);
		UIManager::getInstance()->animateCard(card, 0.35, true);
		deck->discard(card);
	}
	// -------------------------------------------------------------------------
	void Arcomage::animationStarted()
	{
	}

	// -------------------------------------------------------------------------
	void Arcomage::notifyAnimationIdle()
	{
		if(!discardAnimation) {
			UIManager::getInstance()->getPlayerTurn()  ? this->
				applyChanges(player, enemy)
				: this->applyChanges(enemy, player);

			enemy->update();
			player->update();

			// As soon as we're going idle, we'll be playing the sound effects
			// to make everything smooth and stuff
			bool sound_played = false;
			int card = lastCardID;

			// If any damage is dealt, we want to play the damage sound.
			if(deck->getValueFromCard(card, "Damage to Enemy") > 0
				|| deck->getValueFromCard(card, "Damage to Self")) {
				Engine::getInstance()->playSound("damage");
				sound_played = true;
			}

			// If we're going to reduce the tower and/or wall size play the sound as well
			if((deck->getValueFromCard(card, "Enemy Tower Changes") < 0 ||
				deck->getValueFromCard(card, "Enemy Wall Changes")  < 0)
				&& !sound_played) {
				Engine::getInstance()->playSound("damage");
			}

			if((deck->getValueFromCard(card, "Player Tower Changes") > 0 ||
				deck->getValueFromCard(card, "Player Wall Changes")  > 0)
				&& !sound_played) {
				Engine::getInstance()->playSound("gaintowerwall");
				sound_played = true;
			}

			// Determine whether we need to play the harp sound effect
			std::string modifiers[] = {
					"Player Brick Modifier",
					"Player Gem Modifier" ,
					"Player Beast Modifier",
					"Player Brick Changes",
					"Player Gem Changes",
					"Player Beast Changes"};

			bool harp = false, harpdown = false;
			for(int i = 0; i < 6; i++) {
				if(deck->getValueFromCard(card, modifiers[i]) > 0) {
					harp = true;
				} else if(deck->getValueFromCard(card, modifiers[i]) < 0) {
					harpdown = true;
				}
			}

			if((harp || harpdown) && !sound_played) {
				Engine::getInstance()->playSound(harpdown ? "harpdown" :
					"harp");
				doWait = true;
			}
		}
	}
	// -------------------------------------------------------------------------
	void Arcomage::checkStatus(bool isPlayer)
	{
		bool won = false;
		bool lost = false;
		if (status == game_TOWER_MAX || status == game_WALL_MAX) {
			isPlayer? won = true : lost = true;
		} else if (status == game_TOWER_DESTROYED ||
			status == game_WALL_DESTROYED) {
			isPlayer ? lost = true : won = true;
		}

		if(won) {
			UIManager::getInstance()->setText("Game Over Title",
				"You won!");
			UIManager::getInstance()->setText("Game Over Text",
				"You have destroyed your opponent!");
			Engine::getInstance()->playMusic("Victory"), false;
			this->setGamestate(state_END);
		}

		if(lost) {
			UIManager::getInstance()->setText("Game Over Title",
				"You lost!");
			UIManager::getInstance()->setText("Game Over Text",
				"Your opponent has destroyed you!");
			Engine::getInstance()->playMusic("Loss", false);
			this->setGamestate(state_END);
		}

		if(status == game_RESOURCE_MAX) {
			if(isPlayer) {
				UIManager::getInstance()->setText("Game Over Title",
					"You won!");
				UIManager::getInstance()->setText("Game Over Text",
					"You heave reached the resource limit!");
				Engine::getInstance()->playMusic("Victory"), false;
				this->setGamestate(state_END);
			} else {
				UIManager::getInstance()->setText("Game Over Title",
					"You lost!");
				UIManager::getInstance()->setText("Game Over Text",
					"Your opponent has reached the resource limit!");
				Engine::getInstance()->playMusic("Loss", false);
				this->setGamestate(state_END);
			}
		}
	}

	// -------------------------------------------------------------------------
	void Arcomage::animationFinished()
	{
		if(!discardAnimation) {
			int card = lastCardID;

			if(UIManager::getInstance()->getPlayerTurn()) {
				hasToDiscard = deck->getCardByID(card)->discardCard();
				UIManager::getInstance()->
					setTextVisibility("DiscardTextOverlay", hasToDiscard);

				status = player->endRound();
				checkStatus(true);

				enemy->update();
				deck->randomize(card);
				status = enemy->getStatus();
				checkStatus(false);

				if(!deck->getAdditionalTurn(card)) {
					UIManager::getInstance()->setPlayerTurn(false);
				}
			} else {
				status = enemy->endRound();
				player->update();
				checkStatus(false);

				status = player->getStatus();
				checkStatus(true);

				if(deck->getAdditionalTurn(card)) {
					enemy_turn();
				} else if(deck->getCardByID(lastCardID)->discardCard()) {
					hasToDiscard = true;
					enemy_turn();
				} else {
					UIManager::getInstance()->setPlayerTurn(true);
					script->setPlayers(player, enemy);
				}
			}
		} else {
			if(UIManager::getInstance()->getPlayerTurn()) {
				if(hasToDiscard) {
					hasToDiscard = deck->getCardByID(lastCardID)->
						discardCard();
					UIManager::getInstance()->
						setTextVisibility("DiscardTextOverlay",
						hasToDiscard);
					UIManager::getInstance()->setPlayerTurn(true);
				} else {
					UIManager::getInstance()->setPlayerTurn(false);
				}
				status = player->endRound();
				checkStatus(true);

				player->update();
				discardAnimation = false;
			} else {
				checkStatus(false);

				if(hasToDiscard) {
					hasToDiscard = deck->getCardByID(lastCardID)->
						discardCard();
					UIManager::getInstance()->
						setTextVisibility("DiscardTextOverlay",
						hasToDiscard);
					UIManager::getInstance()->setPlayerTurn(false);
					enemy_turn();
				} else {
					UIManager::getInstance()->setPlayerTurn(false);
				}
			}
		}

		// Update the deck, so we can darken cards when there are not enough
		// resources.
		deck->update(player->getAttribute("Bricks"),
			player->getAttribute("Gems"),
			player->getAttribute("Beasts"));
	}

	// -------------------------------------------------------------------------
	void Arcomage::applyChanges(CPlayer* current, CPlayer* other)
	{
		int card = lastCardID;

		// Player changes

		current->setAttribute("Bricks", deck->getValueFromCard(card,
			"Player Brick Changes"));
		current->setAttribute("Gems", deck->getValueFromCard(card,
			"Player Gem Changes"));
		current->setAttribute("Beasts", deck->getValueFromCard(card,
			"Player Beast Changes"));

		current->setAttribute("Brick Modifier", deck->getValueFromCard(card,
			"Player Brick Modifier"));
		current->setAttribute("Gem Modifier", deck->getValueFromCard(card,
			"Player Gem Modifier"));
		current->setAttribute("Beast Modifier", deck->getValueFromCard(card,
			"Player Beast Modifier"));

		current->setAttribute("Tower", deck->getValueFromCard(card,
			"Player Tower Changes"));
		current->setAttribute("Wall", deck->getValueFromCard(card,
			"Player Wall Changes"));
		current->setAttribute("Damage", deck->getValueFromCard(card,
			"Damage to Self"));

		// Enemy Changes
		other->setAttribute("Bricks", deck->getValueFromCard(card,
			"Enemy Brick Changes"));
		other->setAttribute("Gems", deck->getValueFromCard(card,
			"Enemy Gem Changes"));
		other->setAttribute("Beasts", deck->getValueFromCard(card,
			"Enemy Beast Changes"));

		other->setAttribute("Brick Modifier", deck->getValueFromCard(card,
			"Enemy Brick Modifier"));
		other->setAttribute("Gem Modifier", deck->getValueFromCard(card,
			"Enemy Gem Modifier"));
		other->setAttribute("Beast Modifier", deck->getValueFromCard(card,
			"Enemy Beast Modifier"));

		other->setAttribute("Tower", deck->getValueFromCard(card,
			"Enemy Tower Changes"));
		other->setAttribute("Wall", deck->getValueFromCard(card,
			"Enemy Wall Changes"));
		other->setAttribute("Damage", deck->getValueFromCard(card,
			"Damage to Enemy"));

		if (deck->getScript(card) != "0") {
			script->executeFromMemory(deck->getScript(card).c_str());
		}
	}
	// -------------------------------------------------------------------------
	// Event Handler
	void Arcomage::handleEvents()
	{
		// event object
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				if(deck) {
					delete deck;
					deck = 0;
				}

				exit(0);
				break;

				// when a key is pressed
			case SDL_KEYDOWN:

				if (event.key.keysym.sym == SDLK_ESCAPE) {
					if (current_state == state_MENU) {
						exit(SDL_QUIT);
					} else if (current_state == state_CREDITS) {
						this->setGamestate(state_MENU);
						Engine::getInstance()->playMusic("Title");
					} else if (current_state == state_SELECT) {
						this->setGamestate(state_MENU);
					} else if (current_state == state_GAME) {
						this->setGamestate(state_PAUSE);
					} else if (current_state == state_PAUSE) {
						this->setGamestate(state_GAME);
					} else if (current_state == state_END) {
						init[state_LOAD]=false;
						this->setGamestate(state_MENU);
					}
				} else if (event.key.keysym.sym == SDLK_UP) {
					if (current_state == state_SELECT) {
						selected_index--;
						if(selected_index < 0) {
							if(deck_list.size() <= 5) {
								selected_index = deck_list.size()-1;
							} else {
								if(selection_offset > 0) {
									selection_offset--;
								}
								selected_index = 0;
							}
						}
						setSelectionIndex(selected_index);
					}
				} else if (event.key.keysym.sym == SDLK_DOWN) {
					if (current_state == state_SELECT) {
						selected_index++;
						if(selected_index >= 5) {
							if(selection_offset+5 < deck_list.size()) {
								selection_offset++;
							}
							selected_index = 4;
						} else if(selected_index >= deck_list.size()) {
							selected_index = 0;
						}
						setSelectionIndex(selected_index);
					}
				} else if(event.key.keysym.sym == SDLK_F4) {
					//	Uint8 *keystate = SDL_GetKeyboardState(NULL);
					Uint8* keystate = SDL_GetKeyState(NULL);
					if(keystate[SDLK_RALT] || keystate[SDLK_LALT])
						quit_game = true;
				}

				break;
				// mouse motion
			case SDL_MOUSEMOTION:
				Engine::getInstance()->setMousePos( event.motion.x,
					event.motion.y);
				break;

				// mouse click
			case SDL_MOUSEBUTTONDOWN:
				// When we are in the menu screen...
				if (event.button.button == SDL_BUTTON_LEFT) {
					if (current_state == state_MENU && init[state_MENU]) {
						if (UIManager::getInstance()->
							checkMouseOver("New Game")) {
							hasToDiscard = false;
							this->setGamestate(state_SELECT);
						} else if (UIManager::getInstance()->
							checkMouseOver("Credits")) {
							this->setGamestate(state_CREDITS);
						} else if (UIManager::getInstance()->
							checkMouseOver("Exit Game")) {
							this->setGamestate(state_EXIT);
						}
					} else if (current_state == state_END) {
						if (UIManager::getInstance()->
							checkMouseOver("Game Over Main Menu")) {
							init[state_LOAD]=false;
							setGamestate(state_MENU);
						}
					} else if (current_state == state_SELECT) {
						if (UIManager::getInstance()->
							checkMouseOver("Increase")) {
							if (towerlimit == 75) {
								towerlimit = 100;
							} else if (towerlimit == 100) {
								towerlimit = 125;
							}
						} else if (UIManager::getInstance()->
							checkMouseOver("Decrease")) {
							if (towerlimit == 125) {
								towerlimit = 100;
							} else if (towerlimit == 100) {
								towerlimit = 75;
							}
						} else if (UIManager::getInstance()->
							checkMouseOver("Scroll Up")) {
							selected_index--;
							if(selected_index < 0) {
								if(deck_list.size() <= 5) {
									selected_index = deck_list.size()-1;
								} else {
									if(selection_offset > 0) {
										selection_offset--;
									}
									selected_index = 0;
								}
							}
							setSelectionIndex(selected_index);
						} else if (UIManager::getInstance()->
							checkMouseOver("Scroll Down")) {
							selected_index++;
							if(selected_index >= 5) {
								if(selection_offset+5 < deck_list.size()) {
									selection_offset++;
								}
								selected_index = 4;
							} else if(selected_index >= deck_list.size()) {
								selected_index = 0;
							}
							setSelectionIndex(selected_index);
						} else if (UIManager::getInstance()->
							checkTextMouseOver("Selection Line 1")) {
							if(deck_list.size() >= 0) {
								selected_index = 0;
								setSelectionIndex(selected_index);
							}
						} else if (UIManager::getInstance()->
							checkTextMouseOver("Selection Line 2")) {
							if(deck_list.size() > 1) {
								selected_index = 1;
								setSelectionIndex(selected_index);
							}
						} else if (UIManager::getInstance()->
							checkTextMouseOver("Selection Line 3")) {
							if(deck_list.size() > 2) {
								selected_index = 2;
								setSelectionIndex(selected_index);
							}
						} else if (UIManager::getInstance()->
							checkTextMouseOver("Selection Line 4")) {
							if(deck_list.size() > 3) {
								selected_index = 3;
								setSelectionIndex(selected_index);
							}
						} else if (UIManager::getInstance()->
							checkTextMouseOver("Selection Line 5")) {
							if(deck_list.size() > 4) {
								selected_index = 4;
								setSelectionIndex(selected_index);
							}
						} else if (UIManager::getInstance()->
							checkMouseOver("Start Game")) {
							setGamestate(state_LOAD);
						}
						UIManager::getInstance()->setText("Tower Size",
							to_string(towerlimit));
					} else if (current_state == state_GAME) {
						if (!UIManager::getInstance()->
							isAnimationInProgress()) {
							int click = UIManager::getInstance()->
								getCardClicked();
							if (click > 0) {
								lastCardID = click;

								hasToDiscard ? discard(click) : apply(click);
							}
						}
					} else if (current_state == state_PAUSE) {
						if (UIManager::getInstance()->
							checkMouseOver("Main Menu")) {
							init[state_LOAD]=false;
							setGamestate(state_MENU);
						}
					} else if (current_state == state_CREDITS) {
						if (UIManager::getInstance()->
							checkMouseOver("Main Menu C")) {
							setGamestate(state_MENU);
						}
					}
				} else if (event.button.button == SDL_BUTTON_RIGHT) {
					if (current_state == state_GAME) {
						if (!UIManager::getInstance()->
							isAnimationInProgress()) {
							int click = UIManager::getInstance()->
								getCardClicked();
							if (click > 0) {
								lastCardID = click;
								discard(click);
							}
						}
					}
				}
				break;
			}
		}
	}

	// -------------------------------------------------------------------------
	// Main loop
	void Arcomage::run()
	{
		timeSinceLastFrame = (SDL_GetTicks() - last) / 1000.0;

		last = SDL_GetTicks();
		time += timeSinceLastFrame;

		if(time <= 1.0) {
			fps++;
		} else {
			time = 0.0;
			fps = 0;
		}

		if(doWait) {
			//	SDL_Delay(200);
			doWait = false;
		}
		this->handleEvents();

		switch (current_state) {
		case state_CREDITS:
			gs_credits();
			break;
		case state_EXIT:
			SDL_Quit();
			exit(0);
			break;
		case state_GAME:
			gs_game();
			break;
		case state_INTRO:
			gs_startup();
			break;
		case state_LOAD:
			gs_loading();
			break;
		case state_MENU:
			gs_menu();
			break;
		case state_OPTIONS:
			gs_options();
			break;
		case state_PAUSE:
			gs_pause();
			break;
		case state_SELECT:
			gs_select();
			break;
		case state_END:
			if (!UIManager::getInstance()->isAnimationInProgress()) {
				gs_game_over();
			}
			break;
		case state_TUORIAL:
			// gs_tutorial();
			break;
		}

		Engine::getInstance()->render(timeSinceLastFrame);
	}
}
