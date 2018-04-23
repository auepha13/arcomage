/*
 * Arcomage Tribute
 *
 * File: 	ui_manager.h
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
#ifndef UI_MANAGER_H_INCLUDED
#define UI_MANAGER_H_INCLUDED

#include "ui_button.h"
#include "ui_text.h"
#include "ui_image.h"
#include "ui_card.h"
#include "singleton.h"
#include "enumerators.h"
#include "anim_card.h"
#include "ZIPFile.h"

namespace arcomage {
	class Text;
	class Button;
	class Image;
	class CardImage;
	class CardAnimation;
	class AnimationListener;

	class UIManager : public Singleton<UIManager> {
		friend class Singleton<UIManager>;
		// -------------------------------------------------------------------------
		// public
	public:
		// Methods
		~UIManager()
		{
		};
		static UIManager* getInstance()
		{
			return Singleton<UIManager>::getInstance();
		}

		// Add Components
		void addComponent(Component comp,
			std::string comp_name,
			int x,
			int y,
			Gamestate state,
			bool visible);
		void addComponent(Component comp,
			Ptr<Aeon::ZipFile> arch,
			std::string path,
			int x,
			int y,
			Gamestate state,
			bool visible);
		void addComponent(Component comp,
			std::string path,
			std::string comp_name,
			int x,
			int y,
			Gamestate state,
			bool visible);
		void addComponent(Component comp,
			std::string name,
			std::string fa,
			std::string fb,
			int x,
			int y,
			Gamestate state,
			bool visible);
		void addComponent(Component comp,
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
			bool visible);

		// Card Images
		void addCardImage(int id,
			SDL_Surface* picture,
			SDL_Surface* picture_mouseover,
			SDL_Surface* picture_darkened);
		void setCardDarkened(int id, bool state);
		void setVisibleCards(int* pArr);
		int getCardClicked();


		void clearCards();

		// Component ops
		void moveComponent(Component comp, std::string comp_name, int x,
			int y);
		void deleteComponent(Component comp, std::string comp_name);
		void setText(std::string comp_name, std::string pText);
		std::string getText(std::string comp_name);
		void setImageSize(std::string comp_name, int w, int h);
		SDL_Surface* getImage(std::string comp_name);

		// Animation
		void setAnimationCallback(AnimationListener* listener);
		void animateCard(int card_ID, double speed, bool discardAnim =
			false);
		void setPlayerTurn(bool players_turn);
		int getCardPosition(int card_ID);
		void drawCardAt(int id, int x, int y);
		bool isAnimationInProgress();
		bool isCurrentPosBeingAnimated(int pos);
		bool getPlayerTurn()
		{
			return player_turn;
		}
		void setAnimationProgress(bool aprogress)
		{
			animation_in_progress = aprogress;
		}
		void setEnemyAnimationProgress(bool aprogress)
		{
			enemy_anim = aprogress;
		}
		void drawEnemyCards(SDL_Surface* screen, int pos);

		void setTextVisibility(const std::string& compName, bool visible);
		void setImageVisibility(const std::string& compName, bool visible);
		void setImagePos(const std::string& compName, int cardID);
		// unused
		Image* getImageObj(std::string comp_name);
		Text* getTextObj(std::string comp_name);
		Button* getButtonObj(std::string comp_name);

		// Actions
		void registerAction(std::string comp_name, std::string action);
		void unregisterAction(std::string comp_name, std::string action);
		std::string getAction(std::string comp_name);

		// MouseOver Check
		bool checkMouseOver(std::string comp_name);
		bool checkTextMouseOver(std::string comp_name);

		// XML
		void loadFromXML(const char* xml_file, Gamestate state);

		// Render UI
		void renderUI(Gamestate currentState, SDL_Surface* screen,
			double timeSinceLastFrame);

	protected:
		UIManager() : Singleton<UIManager> (), animation(0),
			animationListener(0)
		{
		}

	private:
		std::map<const std::string, Image*> images;
		std::map<const std::string, Button*> buttons;
		std::map<const std::string, Text*> texts;
		std::map<int, CardImage*> cards;
		std::map<const std::string, std::string> actions;
		std::map<int, CardAnimation*> card_anims;
		CardAnimation* animation;
		int visible_cards[6];
		bool init;
		bool player_turn;
		bool animation_in_progress;
		bool enemy_anim;
		AnimationListener* animationListener;
	};
}

#endif // UI_MANAGER_H_INCLUDED
