/*
 * Arcomage Tribute
 *
 * File: 	card.cpp
 * Desc: 	Card class.
 *
 * Date: 	07/2007
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

#include "card.h"

#include "txml/tinyxml.h"

#include "ui_card.h"
#include "ui_text.h"
#include "ui_image.h"

#include "utility.h"
#include "ZipFile.h"

namespace arcomage {

	// -------------------------------------------------------------------------
	Card::Card(int pID, Ptr<Aeon::ZipFile> archive)
		:	discard(false),
		addturn(false),
		mouseover(false),
		ondeck(false),
		darkened(false)
	{

		int temp = 0;

		/* TinyXML init */
		TiXmlDocument doc;
		doc.Parse(archive->unpackAsString("data/deck.xml").c_str());

		TiXmlElement* root = doc.RootElement();

		TiXmlElement* tmp;
		tmp = root->FirstChildElement("Deck");

		TiXmlElement* card;

		/* find given ID */
		for (TiXmlElement* aElement = root->FirstChildElement("Card");
			aElement;
			aElement = aElement->NextSiblingElement("Card")) {
			aElement->Attribute("id", &data["Card ID"]);
			if (data["Card ID"] == pID) {
				root = aElement;
				break;
			}
		}

		/* save the values in variables */
		/* name of the card */
		card = root->FirstChildElement("Name");
		if (card>0) name = card->FirstChild()->ToText()->Value();
		else {
			char err_buffer[255];
			sprintf(err_buffer,
				"*** Error in XML Syntax. Child Element \"Name\" missing in card node of Card %d.",
				pID
				);

			Utility::getInstance()->exitError(err_buffer);
		}
		/* card type */
		card = root->FirstChildElement("Type");
		if (card>0) card->Attribute("value", &data["Type"]);
		else
			Utility::getInstance()->exitError(
				"*** Error in XML Syntax. Child Element \"Type\" missing in card node."
				);

		/* picture filename */
		card = root->FirstChildElement("Picture");
		if (card>0) filename = card->Attribute("value");
		else
			return;

		/* requirements to use the card */
		card = root->FirstChildElement("Requirements");
		if (card>0) card->Attribute("value", &data["Requirements"]);
		else
			data["Requirements"]=0;

		/* additional turn? */
		int addT = 0;
		card = root->FirstChildElement("AdditionalTurn");
		if (card>0) card->Attribute("value", &addT);
		if (addT>0) addturn=true;
		else
			addturn=false;

		int dCard = 0;
		/* discard card? */
		card = root->FirstChildElement("DiscardCard");
		if (card>0) card->Attribute("value", &dCard);
		if (dCard>0) discard=true;
		else
			discard=false;

		/* damage */
		card = root->FirstChildElement("Damage");
		if (card>0) card->Attribute("enemy", &data["Damage to Enemy"]);
		else
			data["Damage to Enemy"]=0;
		if (card>0) card->Attribute("self", &data["Damage to Self"]);
		else
			data["Damage to Self"]=0;

		/* modifiers */
		card = root->FirstChildElement("PlayerChanges"); // player
		if (card>0) {
			card->Attribute("beasts", &data["Player Beast Changes"]);
			card->Attribute("bricks", &data["Player Brick Changes"]);
			card->Attribute("gems", &data["Player Gem Changes"]);
			card->Attribute("tower", &data["Player Tower Changes"]);
			card->Attribute("wall", &data["Player Wall Changes"]);
		} else {
			data["Player Beast Changes"]=0;
			data["Player Brick Changes"]=0;
			data["Player Gem Changes"]=0;
			data["Player Tower Changes"]=0;
			data["Player Wall Changes"]=0;
		}
		card = root->FirstChildElement("EnemyChanges"); // enemy player
		if (card>0) {
			card->Attribute("beasts", &data["Enemy Beast Changes"]);
			card->Attribute("bricks", &data["Enemy Brick Changes"]);
			card->Attribute("gems", &data["Enemy Gem Changes"]);
			card->Attribute("tower", &data["Enemy Tower Changes"]);
			card->Attribute("wall", &data["Enemy Wall Changes"]);
		} else {
			data["Enemy Beast Changes"]=0;
			data["Enemy Brick Changes"]=0;
			data["Enemy Gem Changes"]=0;
			data["Enemy Tower Changes"]=0;
			data["Enemy Wall Changes"]=0;
		}

		/* ressource modifiers */
		card = root->FirstChildElement("PlayerMod"); // player
		if (card>0) {
			card->Attribute("beasts", &data["Player Beast Modifier"]);
			card->Attribute("bricks", &data["Player Brick Modifier"]);
			card->Attribute("gems", &data["Player Gem Modifier"]);

		} else {
			data["Player Beast Modifier"]=0;
			data["Player Brick Modifier"]=0;
			data["Player Gem Modifier"]=0;
		}
		card = root->FirstChildElement("EnemyMod"); // enemy player
		if (card>0) {
			card->Attribute("beasts", &data["Enemy Beast Modifier"]);
			card->Attribute("bricks", &data["Enemy Brick Modifier"]);
			card->Attribute("gems", &data["Enemy Gem Modifier"]);

		} else {
			data["Enemy Beast Modifier"]=0;
			data["Enemy Brick Modifier"]=0;
			data["Enemy Gem Modifier"]=0;
		}

		/* script ID */
		card = root->FirstChildElement("Script");
		if (card>0) script = card->Attribute("value");
		else
			script = "0";

		/* description of the card */
		card = root->FirstChildElement("Description");
		if (card>0) descripton = card->FirstChild()->ToText()->Value();
		else
			Utility::getInstance()->exitError(
				"*** Error in XML Syntax. Child Element \"Description\" missing in card node."
				);

		this->image = this->buildImage(archive);
		UIManager::getInstance()->addCardImage(
			pID,
			image,
			UIManager::getInstance()->getImage("card_mouseover.png"),
			UIManager::getInstance()->getImage("card_darkened.png"));

	}

	// -------------------------------------------------------------------------
	Card::~Card()
	{
		data.clear();
		SDL_FreeSurface(image);
	}

	// -------------------------------------------------------------------------
	SDL_Surface* Card::buildImage(Ptr<Aeon::ZipFile> arch)
	{
		SDL_Surface* temp;

		font_name = Engine::getInstance()->loadfont(ARCHTURA, 16);
		font_desc = Engine::getInstance()->loadfont(ARCHTURA, 12);
		if (data["Type"] == 0) {
			temp = Engine::getInstance()->
				loadImage(arch->unpackRaw("template/images/red.png"));
		} else if (data["Type"] == 1) {
			temp = Engine::getInstance()->
				loadImage(arch->unpackRaw("template/images/blue.png"));
		} else if (data["Type"] == 2) {
			temp = Engine::getInstance()->
				loadImage(arch->unpackRaw("template/images/green.png"));
		} else {
			temp = UIManager::getInstance()->getImage("general_backside.png");
		}


		/* apply rects */
		card_rect.w = temp->w;
		card_rect.h = temp->h;

		card_picture_rect.w = temp->w;
		card_picture_rect.h = temp->h;

		card_picture_rect.x = 20;
		card_picture_rect.y = 56;

		/* split the description by "|" */
		std::string desc_str = "";
		desc_str.append(descripton);

		Utility::getInstance()->Tokenize(desc_str, description_vec, "_n");
		int lines = (int)description_vec.size();

		/* draw the card specific picture to the card */
		SDL_Surface* img = Engine::getInstance()->loadImage(arch->unpackRaw("images/"+filename));
		SDL_BlitSurface(img, 0, temp, &card_picture_rect);
		SDL_FreeSurface(img);

		/* title */
		Text(font_name, 255, 255, 255, 0, name.c_str(), 16, 14, state_GAME,
			true).draw(temp);

		/* create requirements text and draw it on the card */
		// only 2 digits are allowed
		assert(data["Requirements"] < 100);

		Text(font_name, 255, 255, 255, 0, to_string(data["Requirements"]).
			c_str(), (data["Requirements"] < 10) ? 141 : 139, 214,
			state_GAME, true).draw(temp);


		/* check the description's number of lines and draw them to the card */

		for(int i = 0; i < lines; i++) {
			Text text(font_desc,255,255,255,0,
				description_vec[i].c_str(), 16,155+(i*20),
				state_GAME,true);
			text.draw(temp);
		}

		return temp;
	}

	// -------------------------------------------------------------------------
	bool Card::additionalTurn()
	{
		return addturn;
	}

	// -------------------------------------------------------------------------
	bool Card::discardCard()
	{
		return discard;
	}

	// -------------------------------------------------------------------------
	bool Card::checkRequirements(int current_bricks,
		int current_gems,
		int current_beasts)
	{
		switch (data["Type"]) {
		case 0:
			if (current_bricks >= data["Requirements"])
				return true;
			else
				return false;
			break;
		case 1:
			if (current_gems >= data["Requirements"])
				return true;
			else
				return false;
			break;
		case 2:
			if (current_beasts >= data["Requirements"])
				return true;
			else
				return false;
			break;
		default:
			return false;
			break;

		}
	}

	// -------------------------------------------------------------------------
	void Card::setDarkened(bool state)
	{
		this->darkened = state;
	}

	// -------------------------------------------------------------------------
	bool Card::isDarkened()
	{
		return darkened;
	}

	// -------------------------------------------------------------------------
	std::string Card::getName()
	{
		return name;
	}

	// -------------------------------------------------------------------------
	std::string Card::getScript()
	{
		return script;
	}

	// -------------------------------------------------------------------------
	int Card::getValue(std::string attrib)
	{
		return data[attrib];
	}
}
