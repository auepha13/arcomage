/*
 * Arcomage Tribute
 *
 * File:	anim_card.cpp
 * Desc: 	Card Animation class.
 *
 * Date: 	12/2008
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

#include "anim_card.h"
#include "anim_base.h"
#include "ui_manager.h"

namespace arcomage {

	// -------------------------------------------------------------------------
	CardAnimation::CardAnimation(int id,
		int deck_pos,
		int from_x,
		int from_y,
		int to_x,
		int to_y,
		double speed_in_seconds,
		AnimationListener* listener,
		bool isDiscarded /*= false*/)
		: BaseAnimation(from_x, from_y, to_x, to_y, speed_in_seconds),
		discarded(isDiscarded), listener(listener), notified(false)
	{
		card_ID = id;
		this->deck_pos = deck_pos;
	}

	// -------------------------------------------------------------------------
	void CardAnimation::tick(double timeSinceLastFrame)
	{
		move(timeSinceLastFrame);
		draw();
	}
	// -------------------------------------------------------------------------
	void CardAnimation::draw()
	{
		if(discarded && !finished && idle) {
			UIManager::getInstance()->
				setImageVisibility("discard_overlay.png", true);
		} else {
			UIManager::getInstance()->
				setImageVisibility("discard_overlay.png", false);
		}
		if(idle && !notified) {
			UIManager::getInstance()->setImagePos("discard_overlay.png",
				card_ID);
			notified = true;
			listener->notifyAnimationIdle();
		}

		UIManager::getInstance()->drawCardAt(card_ID, int(pos_x),
			int(pos_y));
	}

	// -------------------------------------------------------------------------
	int CardAnimation::getFormerPosition()
	{
		return deck_pos;
	}
}
