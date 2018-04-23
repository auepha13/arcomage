/*
 * Arcomage Tribute
 *
 * File: 	engine.cpp
 * Desc: 	Game Engine, everything technical is handled here.
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
#include "engine.h"


namespace arcomage {

	// -------------------------------------------------------------------------
	// readConfig
	void Engine::readConfig(const char* config)
	{
		Utility::getInstance()->logMessage("arcomage.log",
			std::string("[arcomage::Engine] Reading Config: ")
			.append(config).c_str());

		/* Load Video-Specific settings */
		configuration["screen x"] = Config::getInstance()->
			readInteger("screen", "x", config);
		configuration["screen y"] = Config::getInstance()->
			readInteger( "screen", "y", config);

		configuration["screen color depth"] = Config::getInstance()->
			readInteger("screen", "depth", config);

		configuration["screen fullscreen"] = Config::getInstance()->
			readInteger("screen", "fullscreen", config);
		/* Load Audio-Specific settings */
		configuration["audio bitrate"] = Config::getInstance()->
			readInteger("audio", "rate", config);
		configuration["audio channels"] = Config::getInstance()->
			readInteger("audio", "channels", config);

		configuration["audio buffer"] = Config::getInstance()->
			readInteger("audio", "buffers", config);
		configuration["audio enabled"] = Config::getInstance()->
			readInteger("sound", "enabled", config);

		configuration["effects volume"] = (128 * Config::getInstance()->
			readInteger("effects", "volume", config)) / 100;

		configuration["music volume"] = (128 * Config::getInstance()->
			readInteger("music", "volume", config)) / 100;

		configuration["intro"] = Config::getInstance()->readInteger("intro",
			"display", config);

		std::stringstream config_info;

		config_info << "[arcomage::Config] Config Values are: "
			<< "X"	<< configuration["screen x"]
			<< " Y"	<< configuration["screen y"]
			<< " CD"<< configuration["screen color depth"]
			<< " FS" << configuration["screen fullscreen"]
			<< " ABR"<< configuration["audio bitrate"]
			<< " AC"<< configuration["audio channels"]
			<< " ABF"<< configuration["audio buffer"]
			<< " AE" << configuration["audio enabled"];

		Utility::getInstance()->logMessage("arcomage.log",
			config_info.str().c_str());
	}

	// -------------------------------------------------------------------------
	// init
	void Engine::init(const char* config)
	{
		try {
			if(boost::filesystem::exists("arcomage.log"))
				boost::filesystem::remove("arcomage.log");
		}
		catch (boost::filesystem::filesystem_error& e) {
			std::cerr << e.what();
		}
		std::string version = std::string("Arcomage Tribute ")
			.append(
			AutoVersion::FULLVERSION_STRING
			)
			.append(" ")
			.append(AutoVersion::STATUS)
			.append(" (Build Date: ")
			.append(__DATE__)
			.append(")");

		Utility::getInstance()->logMessage("arcomage.log",version.c_str());
		Utility::getInstance()->logMessage("arcomage.log",
			"*** Created by Xography - http://www.gatewayheaven.com/");
		Utility::getInstance()->logMessage("arcomage.log",
			"[arcomage::Engine] Initializing ...");

		readConfig(config);

		Utility::getInstance()->logMessage("arcomage.log",
			"[arcomage::Engine] Init SDL...");

		// Initialize SDL with Audio
		if (configuration["audio enabled"]) {
			if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
				Utility::getInstance()->exitError(SDL_GetError());
			}
			configuration["audio format"] = AUDIO_S16SYS;

			if (Mix_OpenAudio(configuration["audio bitrate"],
				configuration["audio format"],
				configuration["audio channel"],
				configuration["audio buffer"]) != 0) {
				Utility::getInstance()->exitError(Mix_GetError());
			}
			// Initialize SDL without audio
		} else {
			if (SDL_Init( SDL_INIT_VIDEO) < 0) {
				Utility::getInstance()->exitError(SDL_GetError());
			}
		}

		// Initialize TTF
		if (TTF_Init() == -1) {
			Utility::getInstance()->exitError(TTF_GetError());
		}

		// Define what to do at exit
		atexit(SDL_Quit);

		// Initialize Video
		if (configuration["screen fullscreen"]) {
			screen = SDL_SetVideoMode(configuration["screen x"],
				configuration["screen y"],
				configuration["screen color depth"],
				SDL_FULLSCREEN|SDL_HWSURFACE|SDL_DOUBLEBUF);
		} else {
			screen = SDL_SetVideoMode(configuration["screen x"],
				configuration["screen y"],
				configuration["screen color depth"],
				SDL_HWSURFACE|SDL_DOUBLEBUF);
		}

		SDL_WM_SetCaption(version.c_str(),version.c_str());

		if (!screen) {
			Utility::getInstance()->exitError(SDL_GetError());
		}

		Utility::getInstance()->logMessage("arcomage.log",
			"[arcomage::Engine] initialized successfully.");

		Utility::getInstance()->logMessage("arcomage.log",
			"[arcomage::Engine] Trying to preload music...");
		// preload music
		this->loadMusic();

		// preload sounds
		this->loadSounds();

		if(configuration["audio enabled"])
			Mix_Volume(-1, configuration["effects volume"]);
	}


	// -------------------------------------------------------------------------
	Engine::~Engine()
	{
		std::map<const std::string, TTF_Font*>::iterator it;
		for(it = fonts.begin(); it != fonts.end(); it++) {
			TTF_CloseFont(it->second);
		}
		std::map<const std::string, SDL_Surface*>::iterator it_images;
		for(it_images = images.begin(); it_images != images.end();
			it_images++) {
			SDL_FreeSurface(it_images->second);
		}

		Mix_HaltMusic();
		std::map<const std::string, Mix_Music*>::iterator it_music;
		for(it_music = music.begin(); it_music != music.end();
			it_music++) {
				Mix_FreeMusic(it_music->second);
		} 

		Mix_HaltChannel(-1);
		std::map<const std::string, Mix_Chunk*>::iterator it_sounds;
		for(it_sounds = sounds.begin(); it_sounds != sounds.end();
			it_sounds++) {
				Mix_FreeChunk(it_sounds->second);
		}

		 Mix_CloseAudio();
		 Mix_Quit();
	}

	// -------------------------------------------------------------------------
	// music loader
	void Engine::loadMusic()
	{
		TiXmlDocument doc(MUSIC_FILE);

		if (!doc.LoadFile()) {
			Utility::getInstance()->exitError(doc.ErrorDesc());
		}

		TiXmlElement* root = doc.RootElement();
		TiXmlElement* track;

		Utility::getInstance()->logMessage("arcomage.log",
			std::string("[arcomage::Engine] Reading ")
			.append(MUSIC_FILE).c_str());

		for (TiXmlElement* aElement = root->FirstChildElement("Track");
			aElement;
			aElement = aElement->NextSiblingElement("Track")) {
			track = aElement->FirstChildElement("Name");
			std::string name = track->Attribute("value");

			track = aElement->FirstChildElement("File");
			std::string file = track->Attribute("value");

			std::string path = MUSIC_P;
			path=path.append(file);

			music[name] = Mix_LoadMUS(path.c_str());
			Utility::getInstance()->logMessage("arcomage.log",
				std::string("[arcomage::Engine] Loaded ")
				.append(file).c_str());

			if (music[name] == NULL) {
				Utility::getInstance()->logMessage("audio_error.log",
					Mix_GetError());
			}
		}
	}

	// -------------------------------------------------------------------------
	// play music
	void Engine::playMusic(std::string track, bool loop /*= true*/)
	{
		//  Mix_FadeOutMusic(750);

		if (configuration["audio enabled"]) {
			Mix_VolumeMusic(configuration["music volume"]);
			if (Mix_PlayMusic(music[track], loop ? 1 : 0) == -1) {
				Utility::getInstance()->logMessage("audio_error.log",
					Mix_GetError());
			}

		}
	}

	// -------------------------------------------------------------------------
	// play music
	void Engine::stopMusic()
	{
		Mix_FadeOutMusic(0);
	}

	// -------------------------------------------------------------------------
	void Engine::loadSounds()
	{
		sounds["card"] = Mix_LoadWAV("data/sounds/card.wav");
		sound_channels["card"] = -1;

		sounds["damage"] = Mix_LoadWAV("data/sounds/damage.wav");
		sound_channels["damage"] = -1;

		if (sounds["card"] == NULL) {
			Utility::getInstance()->logMessage("audio_error.log",
				Mix_GetError());
		}

		sounds["harp"] = Mix_LoadWAV("data/sounds/harp.wav");
		sound_channels["harp"] = -1;

		sounds["harpdown"] = Mix_LoadWAV("data/sounds/resourceloss.wav");
		sound_channels["harpdown"] = -1;


		sounds["gaintowerwall"] =
			Mix_LoadWAV("data/sounds/towerwallgain.wav");
		sound_channels["gaintowerwall"] = -1;


		if (sounds["harp"] == NULL) {
			Utility::getInstance()->logMessage("audio_error.log",
				Mix_GetError());
		}

	}

	// -------------------------------------------------------------------------
	// play sound
	void Engine::playSound(std::string sound)
	{
		if (configuration["audio enabled"]) {
			if(sound_channels[sound] < 0) {

				sound_channels[sound] = Mix_PlayChannel(sound_channels[
					sound], sounds[sound], 0);
				sound_channels[sound] = -1;
			} else {
				Mix_HaltChannel(sound_channels[sound]);
				sound_channels[sound] = -1;
			}
		}
	}
	// -------------------------------------------------------------------------
	// sound enabled or not?
	bool Engine::getSoundEnabled()
	{
		return (configuration["audio enabled"] == 1);
	}
	// -------------------------------------------------------------------------
	// Load image
	SDL_Rect Engine::getCenter()
	{
		SDL_Rect box;
		box.x = configuration["screen x"]/2;
		box.y = configuration["screen y"]/2;

		return box;
	}
	// -------------------------------------------------------------------------
	// From Archive
	SDL_Surface* Engine::loadImage(Aeon::RawMemoryBlock data)
	{
		SDL_Surface* destsurf = NULL;
		SDL_RWops* rwop;

		// create the surface from memory
		rwop = SDL_RWFromMem(data.ptr, data.length);

		if (!rwop) {
			Utility::getInstance()->exitError(
				std::string("*** Unable to open image.")
				.append(". Image not found or invalid file format.").c_str()
				);
		}
		if (IMG_isBMP(rwop)) {
			destsurf = IMG_LoadBMP_RW(rwop);
		} else if (IMG_isPNG(rwop)) {
			destsurf = IMG_LoadPNG_RW(rwop);
		} else if (IMG_isJPG(rwop)) {
			destsurf = IMG_LoadJPG_RW(rwop);
		} else if (IMG_isGIF(rwop)) {
			destsurf = IMG_LoadGIF_RW(rwop);
		}

		SDL_FreeRW(rwop);

		return destsurf;
	}

	// -------------------------------------------------------------------------
	// From File
	SDL_Surface* Engine::loadImage(const std::string& file,
		bool loadCopy /* = false */)
	{

		SDL_Surface* destsurf = NULL;
		SDL_RWops* rwop;
		rwop = SDL_RWFromFile(file.c_str(), "rb");

		if (!rwop) {
			Utility::getInstance()->exitError(
				std::string("*** Unable to open ")
				.append(file)
				.append(". Image not found or invalid file format.").c_str()
				);
		}
		if (IMG_isBMP(rwop)) {
			destsurf = IMG_LoadBMP_RW(rwop);
		} else if (IMG_isPNG(rwop)) {
			destsurf = IMG_LoadPNG_RW(rwop);
		} else if (IMG_isJPG(rwop)) {
			destsurf = IMG_LoadJPG_RW(rwop);
		} else if (IMG_isGIF(rwop)) {
			destsurf = IMG_LoadGIF_RW(rwop);
		}
		if(rwop) {
			SDL_FreeRW(rwop);
		}
		return destsurf;
		/*
		images[fname] = destsurf;

		return images[fname];*/
	}

	// -------------------------------------------------------------------------
	// Load Font
	TTF_Font* Engine::loadfont(const char* file, int ptsize)
	{
		std::stringstream strstr;
		strstr << file << ptsize;
		std::string fontName = strstr.str();

		if(fonts[fontName] != 0) {
			return fonts[fontName];
		}

		TTF_Font* tmpfont;
		tmpfont = TTF_OpenFont(file, ptsize);
		if (tmpfont == NULL) {
			Utility::getInstance()->exitError(TTF_GetError());
		}
		#if TTF_PATCHLEVEL >= 10
			TTF_SetFontHinting(tmpfont, TTF_HINTING_LIGHT);
		#else
			//TTF_SetFontHinting(tmpfont, TTF_HINTING_NORMAL);
		#endif

		fonts[fontName] = tmpfont;
		return fonts[fontName];
	}


	// -------------------------------------------------------------------------
	// Draw Text
	SDL_Surface* Engine::drawtext(TTF_Font* fonttodraw, int fgR, int fgG,
		int fgB,
		int fgA, int bgR, int bgG, int bgB, int bgA,
		const char* text, textquality quality)
	{
		SDL_Surface* destsurf = NULL;
		SDL_Color tmpfontcolor = {fgR,fgG,fgB,fgA};
		SDL_Color tmpfontbgcolor = {bgR, bgG, bgB, bgA};
		if (quality == solid) {
			destsurf = TTF_RenderText_Solid(fonttodraw, text, tmpfontcolor);
		} else if (quality == shaded) {
			destsurf = TTF_RenderText_Shaded(fonttodraw,
				text,
				tmpfontcolor,
				tmpfontbgcolor);
		} else if (quality == blended) {
			destsurf = TTF_RenderText_Blended(fonttodraw, text,
				tmpfontcolor);
		}

		return destsurf;
	}

	// -------------------------------------------------------------------------
	// set mouse position
	void Engine::setMousePos(int mx, int my)
	{
		mouse_x = mx;
		mouse_y = my;
	}

	// -------------------------------------------------------------------------
	// check whether the mouse is over the given rectangle
	bool Engine::checkMouseOver(SDL_Rect target)
	{
		if ((mouse_x > target.x)
			&& (mouse_x < target.x + target.w)
			&& (mouse_y > target.y)
			&& (mouse_y < target.y + target.h)) {
			return true;
		}

		return false;
	}
	// -------------------------------------------------------------------------
	// render
	void Engine::render(double timeSinceLastFrame)
	{
		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));

		UIManager::getInstance()->renderUI(game->getGamestate(), screen,
			timeSinceLastFrame);
		SDL_Flip(screen);
	}
}
