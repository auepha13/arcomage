/*
 * Arcomage Tribute
 *
 * File: 	ui_manager.cpp
 * Desc: 	UI Manager class, managing & rendering all UI objects.
 *
 * Date: 	06/2007
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
#include "ui_manager.h"
#include "ZIPFile.h"

namespace arcomage {

	// -------------------------------------------------------------------------
	// Add Image
	void UIManager::addComponent(Component comp,
		std::string file,
		int x, int y,
		Gamestate state,
		bool visible)
	{
		assert(comp==IMAGE);
		std::string img_f = GFX_P;
		img_f.append(file);

		images[file] = new Image(
			x,
			y,
			Engine::getInstance()->loadImage(img_f),
			state,visible
			);
	}
	// -------------------------------------------------------------------------
	// Add Image from a non default path
	void UIManager::addComponent(Component comp,
		std::string path,
		std::string file,
		int x, int y,
		Gamestate state,
		bool visible)
	{
		assert(comp==IMAGE);
		std::string img_f = path;
		img_f.append(file);

		images[file] = new Image(
			x,
			y,
			Engine::getInstance()->loadImage(img_f),
			state,visible
			);
	}

	// -------------------------------------------------------------------------
	// Add Image from an archive
	void UIManager::addComponent(Component comp,
		Ptr<Aeon::ZipFile> arch,
		std::string path,
		int x, int y,
		Gamestate state,
		bool visible)
	{
		images[boost::filesystem::path(path).filename()] = new Image(
			x,
			y,
			Engine::getInstance()->loadImage(arch->unpackRaw(path)),
			state,visible
			);
	}

	// -------------------------------------------------------------------------
	void UIManager::setTextVisibility(const std::string& compName,
		bool visible)
	{
		texts[compName]->setVisibility(visible);
	}

	// -------------------------------------------------------------------------
	void UIManager::setImageVisibility(const std::string& compName,
		bool visible)
	{
		images[compName]->setVisibility(visible);
	}

	// -------------------------------------------------------------------------
	// Add Button
	void UIManager::addComponent(Component comp,
		std::string name,
		std::string fa,
		std::string fb,
		int x, int y,
		Gamestate state,
		bool visible)
	{
		assert(comp==BUTTON);
		std::string file_a = BUTTON_P;
		std::string file_b = file_a;
		file_a.append(fa);
		file_b.append(fb);

		buttons[name] = new Button(x,
			y,
			Engine::getInstance()->loadImage(file_a),
			Engine::getInstance()->loadImage(file_b),
			state,
			visible);
	}

	// -------------------------------------------------------------------------
	// Add Text
	void UIManager::addComponent(Component comp,
		std::string name,
		const char* text,
		const char* fontfile,
		int size,
		int x,
		int y,
		int fgR,
		int fgG,
		int fgB,
		Gamestate state,
		bool visible)
	{
		assert(comp==TEXT);
		TTF_Font* temp = Engine::getInstance()->loadfont(fontfile, size);
		texts[name] = new Text(temp, fgR, fgG, fgB, 0 , text, x, y, state,
			true);
	}

	// -------------------------------------------------------------------------
	// Delete Component
	void UIManager::deleteComponent(Component comp, std::string comp_name)
	{
		if (comp == BUTTON) {
			buttons.erase(buttons.find(comp_name));
		} else if (comp == IMAGE) {
			std::map<const std::string, Image*>::iterator it = images.find(comp_name);
			if(it != images.end()) {
				images.erase(it);
			}
		} else if (comp == TEXT) {
			texts.erase(texts.find(comp_name));
		}

	}

	// -------------------------------------------------------------------------
	// Load UI from XML
	void UIManager::loadFromXML(const char* xml_file, Gamestate state)
	{
		std::string xml_path = XML_PATH;
		xml_path.append(xml_file);

		Utility::getInstance()->logMessage(
			"arcomage.log",
			std::string("[arcomage::UIManager] Loading UI definitions from ")
			.append(xml_path).c_str()
			);

		TiXmlDocument doc(xml_path.c_str());

		if (!doc.LoadFile()) {
			Utility::getInstance()->exitError(doc.ErrorDesc());
		}

		TiXmlElement* root = doc.RootElement();


		TiXmlElement* aComponent;


		for (TiXmlElement* aElement = root->FirstChildElement("Component");
			aElement;
			aElement = aElement->NextSiblingElement("Component")) {

			std::string comp_type = aElement->Attribute("type");

			std::string name;
			std::string file_a;
			std::string file_b;
			std::string align;
			std::string action;
			std::string text;

			SDL_Rect centerpoint = Engine::getInstance()->getCenter();

			int x, y, r, g, b, size;

			bool visible = true;

			if (comp_type == "Image") {
				aComponent = aElement->FirstChildElement("file");
				name = aComponent->Attribute("name");
			} else if (comp_type == "Button") {
				aComponent = aElement->FirstChildElement("name");
				name = aComponent->Attribute("value");

				aComponent = aElement->FirstChildElement("file");
				file_a = aComponent->Attribute("normal");

				aComponent = aElement->FirstChildElement("file");
				file_b = aComponent->Attribute("hover");
			} else if (comp_type == "Text") {
				aComponent = aElement->FirstChildElement("name");
				name = aComponent->Attribute("value");

				aComponent = aElement->FirstChildElement("caption");
				text = aComponent->Attribute("value");

				aComponent = aElement->FirstChildElement("font");
				aComponent->Attribute("size", &size);

				aComponent = aElement->FirstChildElement("color");
				aComponent->Attribute("r", &r);
				aComponent->Attribute("g", &g);
				aComponent->Attribute("b", &b);
			}

			aComponent = aElement->FirstChildElement("position");
			aComponent->Attribute("x", &x);
			aComponent->Attribute("y", &y);
			align = aComponent->Attribute("align");

			if (align == "center") {
				x = centerpoint.x+x;
				y = centerpoint.y+y;
			}

			aComponent = aElement->FirstChildElement("visible");

			if (aComponent->Attribute("visible") == "false")
				visible=false;

			if (comp_type == "Button") {
				aComponent = aElement->FirstChildElement("action");
				action = aComponent->Attribute("name");
			}

			if (comp_type == "Image") {
				this->addComponent(IMAGE, name, x, y, state, visible);
			} else if (comp_type == "Button") {
				this->addComponent(BUTTON, name, file_a, file_b, x, y, state,
					visible);
				this->registerAction(name, action);
			} else if (comp_type == "Text") {
				this->addComponent(TEXT, name, text.c_str(), KINGTHINGS,
					size, x, y, r, g, b, state, visible);
			}

			Utility::getInstance()->logMessage("arcomage.log",
				std::string("[arcomage::UIManager] Added Component [").
				append(comp_type).append("] ").append(name).c_str());
		}
	}
	// -------------------------------------------------------------------------
	// Add a new Card
	void UIManager::addCardImage(int id,
		SDL_Surface* picture,
		SDL_Surface* picture_mouseover,
		SDL_Surface* picture_darkened)
	{
		cards[id] = new CardImage(picture, picture_mouseover,
			picture_darkened);
	}

	// -------------------------------------------------------------------------
	void UIManager::clearCards()
	{
		if(!cards.empty())
			cards.clear();
	}
	// -------------------------------------------------------------------------
	// Set darkened state
	void UIManager::setCardDarkened(int id, bool state)
	{
		cards[id]->setDarkened(state);
	}
	// -------------------------------------------------------------------------
	// Set which cards are visible on the screen
	int UIManager::getCardPosition(int card_ID)
	{
		assert(init = true);

		for (int i = 0; i<6; i++) {
			if (visible_cards[i] == card_ID) {
				return i;
			}
		}

		// Error; a card which is not on the screen cannot be clicked.
		return -1;
	}
	// -------------------------------------------------------------------------
	// Set which cards are visible on the screen
	void UIManager::setVisibleCards(int* pArr)
	{
		for (int i = 0; i<6; i++) {
			visible_cards[i] = pArr[i];
		}

		init = true;
	}

	// -------------------------------------------------------------------------
	// Set whether it's the player's turn or not (required by animations)
	void UIManager::setPlayerTurn(bool players_turn)
	{
		this->player_turn = players_turn;
	}

	// -------------------------------------------------------------------------
	// Check whether a card was clicked
	// Returns 0 when no card was clicked
	// Returns the Card Number, when a card was clicked
	int UIManager::getCardClicked()
	{
		for (std::map<int, CardImage*>::const_iterator it = cards.begin();
			it != cards.end(); ++it) {
			if (it->second->isVisible() && it->second->isMouseOver()) {
				return it->first;
			}
		}
		return 0;
	}

	// -------------------------------------------------------------------------
	// Register Action
	void UIManager::registerAction(std::string comp_name, std::string action)
	{
		this->actions[comp_name] = action;
	}

	// -------------------------------------------------------------------------
	// get Action
	std::string UIManager::getAction(std::string comp_name)
	{
		return actions[comp_name];
	}

	// -------------------------------------------------------------------------
	// Check whether the mouse is over a specific button
	bool UIManager::checkMouseOver(std::string comp_name)
	{
		return buttons[comp_name] != 0 ? Engine::getInstance()->checkMouseOver(buttons[comp_name]->getRect()) : false;

	}

	// -------------------------------------------------------------------------
	bool UIManager::checkTextMouseOver(std::string comp_name)
	{
		return Engine::getInstance()->checkMouseOver(
			texts[comp_name]->getRect()
			);
	}
	// -------------------------------------------------------------------------
	// set Text
	void UIManager::setText(std::string comp_name, std::string pText)
	{
		texts[comp_name]->setText(pText);
	}

	// -------------------------------------------------------------------------
	// set Image Size
	void UIManager::setImageSize(std::string comp_name, int w, int h)
	{
		images[comp_name]->setSize(w, h);
	}

	// -------------------------------------------------------------------------
	// Move Component
	void UIManager::moveComponent(Component comp, std::string comp_name,
		int x, int y)
	{
		if (comp == IMAGE) {
			images[comp_name]->setPos(x, y);
		} else if (comp == TEXT) {
			texts[comp_name]->setPos(x, y);
		} else if (comp == BUTTON) {
			buttons[comp_name]->setPos(x, y);
		}
	}
	// -------------------------------------------------------------------------
	// get Image
	SDL_Surface* UIManager::getImage(std::string comp_name)
	{
		return images[comp_name]->getSurface();
	}
	// -------------------------------------------------------------------------
	// get Text
	std::string UIManager::getText(std::string comp_name)
	{
		return texts[comp_name]->getText();
	}
	// -------------------------------------------------------------------------
	// Animation Manager
	void UIManager::animateCard(int card_ID, double speed,
		bool discardAnim /*= false*/)
	{
		int position;
		SDL_Rect pos;

		if (player_turn) {
			position = getCardPosition(card_ID);
		} else {
			// since the enemy has no visible card deck, we randomize
			// a position to animate the card from...
			enemy_anim = true;
			int lowest = 0, highest = 5;
			int range = (highest-lowest);
			position = lowest+int(range*rand()/(RAND_MAX + 1.0));
		}

		pos.y=510;

		switch (position) {
		case 0:
			pos.x=10;
			break;
		case 1:
			pos.x=10+167;
			break;
		case 2:
			pos.x=10+167*2;
			break;
		case 3:
			pos.x=10+167*3;
			break;
		case 4:
			pos.x=10+167*4;
			break;
		case 5:
			pos.x=10+167*5;
			break;
		default:
			pos.x=0;
			break;
		}
		// since we can't animate the card more than once at the same moment
		// we identify the animations using the card's id

		// destination is the Center Point of the screen
		card_anims[card_ID] = new CardAnimation(
			card_ID,
			position,
			pos.x,
			pos.y,
			Engine::getInstance()->getCenter().x-100,
			Engine::getInstance()->getCenter().y-150,
			speed,
			animationListener,
			discardAnim
			);

		cards[card_ID]->setAnimated(true);
		this->animation_in_progress = true;
	}

	// -------------------------------------------------------------------------
	void UIManager::setImagePos(const std::string& compName, int cardID)
	{
		images[compName]->setPos(cards[cardID]->getRect().x,
			cards[cardID]->getRect().y);
	}

	// -------------------------------------------------------------------------
	void UIManager::drawCardAt(int id, int x, int y)
	{
		cards[id]->drawAt(Engine::getInstance()->getScreen(), x, y);
		images["discard_overlay.png"]->draw(Engine::getInstance()->
			getScreen());
	}

	// -------------------------------------------------------------------------
	bool UIManager::isAnimationInProgress()
	{
		return animation_in_progress;
	}

	// -------------------------------------------------------------------------
	bool UIManager::isCurrentPosBeingAnimated(int pos)
	{
		for (std::map<int, CardAnimation*>::const_iterator it = card_anims.
			begin();
			it != card_anims.end();
			++it) {
			if (it->second->getFormerPosition() == pos) {
				return true;
			}
		}
		return false;

	}

	// -------------------------------------------------------------------------
	void UIManager::drawEnemyCards(SDL_Surface* screen, int pos)
	{
		images["general_backside.png"]->setVisibility(true);

		for (int i = 0; i<6; i++) {
			images["general_backside.png"]->setPos(10+167*i, 510);

			if (pos != i) {
				images["general_backside.png"]->draw(screen);
			}
		}
	}
	// -------------------------------------------------------------------------
	void UIManager::setAnimationCallback(AnimationListener* listener)
	{
		this->animationListener = listener;
	}
	// -------------------------------------------------------------------------
	// Render the UI to the screen.
	void UIManager::renderUI(Gamestate currentState, SDL_Surface* screen,
		double timeSinceLastFrame)
	{
		for (std::map<const std::string, Image*>::const_iterator it = images.
			begin(); it != images.end(); ++it) {
			if (it->second->getAssociatedGamestate() == currentState) {
				it->second->draw(screen);
			}
		}

		// Render Buttons
		for (std::map<const std::string, Button*>::const_iterator it =
			buttons.begin();
			it != buttons.end();
			++it) {
			if(it->second != 0) {
				it->second->mouseOver();
				if (it->second->getAssociatedGamestate() == currentState) {
					it->second->draw(screen);
				}
			}
		}

		// Render Text
		for (std::map<const std::string, Text*>::const_iterator it = texts.
			begin(); it != texts.end(); ++it) {
			if (it->second->getAssociatedGamestate() == currentState) {
				it->second->draw(screen);
			}
		}


		// Render Cards
		for (std::map<int, CardImage*>::const_iterator it = cards.begin();
			it != cards.end();
			++it) {
			if (it->second->getAssociatedGamestate() == currentState) {
				it->second->setVisibility(false);
				for (int i = 0; i<6; i++) {
					if (visible_cards[i] == it->first) {
						if (!isCurrentPosBeingAnimated(i)) {
							it->second->setVisibility(true);
						}

						if (!enemy_anim) {
							images["general_backside.png"]->
								setVisibility(false);
							it->second->draw(screen, i);
						}
					}
				}
			}
		}

		// Render Animation
		if(!card_anims.empty() && animationListener &&
			animationListener->getState() == state_GAME) {
			int pos = 0;
			bool delete_entry = false;
			bool animationAborted = false;
			std::map<int, CardAnimation*>::const_iterator it = card_anims.
				begin();


			if (!it->second->isFinished()) {
				// Abort Animation if we leave the Game state
				if(animationListener->getState() != state_GAME) {
					animation_in_progress = false;
					cards[it->first]->setAnimated(false);
					pos = it->first;
					delete_entry = true;
					animationAborted = true;
				} else {
					animation_in_progress = true;
				}

				if (enemy_anim && animation_in_progress) {
					drawEnemyCards(screen, it->second->getFormerPosition());
				}

				if(animation_in_progress) {
					it->second->tick(timeSinceLastFrame);
				}

			} else {
				cards[it->first]->setAnimated(false);
				pos = it->first;
				delete_entry = true;
			}

			if(delete_entry) {
				card_anims.erase(pos);
				if(card_anims.empty()) {
					animation_in_progress = false;


					if (enemy_anim && card_anims.empty()) {
						enemy_anim = false;
					}

					// Surpress listener notification if the animation was aborted,
					// since the game is over anyway then.
					if(animationListener)
						animationListener->animationFinished();
				}


			}

		}



	}
}
