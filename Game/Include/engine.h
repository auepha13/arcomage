/*
 * Arcomage Tribute
 *
 * File: engine.h
 * Desc: SDL Wrapper / Singleton
 *
 * Date: 12/2008
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


#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED


#include "AeonCompress.h" 
#include "game.h"

namespace arcomage {
	class Arcomage;
	class Image;
	class Text;
	class Button;
	
	class Engine : public Singleton<Engine> {
		friend class Singleton<Engine>;
		// -------------------------------------------------------------------------
		// public
	public:
		// Methods
		~Engine();
		static Engine* getInstance()
		{
			return Singleton<Engine>::getInstance();
		}
		void init(const char* config);
		void setGame(Arcomage* p)
		{
			game = p;
		}

		bool getSoundEnabled();
		bool getIntroEnabled()
		{
			if(configuration["intro"])
				return true;
			else
				return false;
		}
		// SDL_Surface* getScreen();

		// Music
		void playMusic(std::string track, bool loop = true);
		void stopMusic();

		// Sounds
		void playSound(std::string sound);

		// Positions
		SDL_Rect getCenter();
		void setMousePos( int mx, int my);
		bool checkMouseOver(SDL_Rect target);

		// Images
		SDL_Surface* loadImage(const std::string& file, bool loadCopy = false);
		SDL_Surface* loadImage(Aeon::RawMemoryBlock data);

		// Text
		SDL_Surface* drawtext(TTF_Font* fonttodraw, int fgR, int fgG,
			int fgB,
			int fgA, int bgR, int bgG, int bgB, int bgA,
			const char* text, textquality quality);

		TTF_Font* loadfont(const char* file, int ptsize);

		SDL_Surface* getScreen()
		{
			return screen;
		}

		// Render
		void render(double timeSinceLastFrame);
		void render_Image( const std::pair<std::string, Image*> p );
		// -------------------------------------------------------------------------
		// protected
	protected:
		Engine() : Singleton<Engine> ()
		{

		}
		// -------------------------------------------------------------------------
		// private
	private:
		// Attributes
		SDL_Surface* screen;
		friend class Arcomage;
		Arcomage* game;

		// STL Containers
		std::map<const std::string, int> configuration;
		std::map<const std::string, Mix_Music*> music;
		std::map<const std::string, Mix_Chunk*> sounds;
		std::map<const std::string, int> sound_channels;
		std::map<const std::string, TTF_Font*> fonts;
		std::map<const std::string, SDL_Surface*> images;

		// Mouse Position
		int mouse_x;
		int mouse_y;

		// Application State
		int app_state;

		// Methods
		void readConfig(const char* config);
		void loadMusic();
		void loadSounds();
	};

}

#endif // ENGINE_H_INCLUDED
