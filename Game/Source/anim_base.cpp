/*
 * Arcomage Tribute
 *
 * File: 	anim_base.cpp
 * Desc: 	Basic Animation class.
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

#include "anim_base.h"
#include "defines.h"

namespace arcomage {

	// -------------------------------------------------------------------------
	BaseAnimation::BaseAnimation(int from_x, int from_y,
		int to_x, int to_y,
		double anim_speed)
		: time(2 * anim_speed), currentTime(0.0), idle(false)
	{
		assert( anim_speed > 0 );
		this->from_x = from_x;
		this->from_y = from_y;
		this->to_x = to_x;
		this->to_y = to_y;

		finished = false;
		// animation speed
		speed = anim_speed;
		this->calc();
	}

	// -------------------------------------------------------------------------
	bool BaseAnimation::isFinished()
	{
		return finished;
	}

	// -------------------------------------------------------------------------
	void BaseAnimation::calc()
	{
		// calculate the distance to shift per tick
		pos_x = double(from_x);
		pos_y = double(from_y);

		shift_x = (to_x - from_x) / speed;
		shift_y = (to_y - from_y)  / speed;
	}
	// -------------------------------------------------------------------------
	void BaseAnimation::tick(double timeSinceLastFrame )
	{
		this->move(timeSinceLastFrame);
		this->draw();
	}

	// -------------------------------------------------------------------------
	void BaseAnimation::move(double timeSinceLastFrame)
	{

		if (shift_x < 0) {
			if (to_x >= pos_x || to_y >= pos_y) {
				idle = true;
				currentTime += timeSinceLastFrame;
				finished= currentTime >= time;

			} else {
				pos_x += shift_x *  timeSinceLastFrame;
				pos_y += shift_y *  timeSinceLastFrame;
			}
		} else {
			if (to_x <= pos_x || to_y >= pos_y) {
				idle = true;
				currentTime += timeSinceLastFrame;
				finished= currentTime >= time;

			} else {
				pos_x += shift_x *  timeSinceLastFrame;
				pos_y += shift_y *  timeSinceLastFrame;
			}
		}
	}
}
