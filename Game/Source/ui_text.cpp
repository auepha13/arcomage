/*
 * Arcomage Tribute
 *
 * File: 	ui_text.cpp
 * Desc: 	Basic Text Display
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
#include "ui_text.h"

namespace arcomage {
	// -------------------------------------------------------------------------
	// <<constructor>>
	Text::Text(TTF_Font* pFont,
		int pR,
		int pG,
		int pB,
		int pAlpha,
		const char* pText,
		int x,
		int y,
		Gamestate state,
		bool visible)
		: Object(x,y,state,visible)
	{
		font = pFont;
		R = pR;
		G = pG;
		B = pB;
		alpha = pAlpha;
		text = pText;
		this->renderText();
	}

	// -------------------------------------------------------------------------
	// <<destructor>>
	Text::~Text()
	{
		SDL_FreeSurface(text_surf);
	}

	// -------------------------------------------------------------------------
	// Store Text in Surface
	void Text::renderText()
	{
		SDL_Color color = {R,G,B};
		text_surf = TTF_RenderText_Blended(font, text.c_str(), color);

	}
	// -------------------------------------------------------------------------
	// draw the text
	void Text::draw(SDL_Surface* dest)
	{
		if(visible)
			SDL_BlitSurface(text_surf, NULL, dest, &pos);
	}

	// -------------------------------------------------------------------------
	//  change the caption
	void Text::setText(std::string pText)
	{
		text = pText;
		SDL_FreeSurface(text_surf);
		this->renderText();
	}

	// -------------------------------------------------------------------------
	// get the text
	std::string Text::getText()
	{
		return text;
	}

	// -------------------------------------------------------------------------
	//  change the color
	void Text::setColor(int pR, int pG, int pB)
	{
		R = pR;
		G = pG;
		B = pB;
	}

	// -------------------------------------------------------------------------
	//  set the text's alpha value
	void Text::setAlpha(int pAlpha)
	{
		alpha = pAlpha;
	}

	// -------------------------------------------------------------------------
	//  set the background alpha (UNUSED) */
	void Text::setBackgroundAlpha(int pBGAlpha)
	{
		bgalpha = pBGAlpha;
	}
}
