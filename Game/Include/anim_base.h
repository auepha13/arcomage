/*
 * Arcomage Tribute
 *
 * File: anim_base.h
 * Desc: Basic animation class
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
#ifndef ANIM_BASE_H_INCLUDED
#define ANIM_BASE_H_INCLUDED

#include <cmath>
#include <assert.h>
#include <stdio.h>
#include "ArcomageForward.h"

namespace arcomage {

	class BaseAnimation {

	public:
		BaseAnimation(int from_x, int from_y, int to_x, int to_y,
			double anim_speed);
		virtual ~BaseAnimation()
		{
		}
		bool isFinished();
		virtual void tick(double timeSinceLastFrame);
		virtual void draw() = 0;

	protected:
		double time, currentTime;
		bool finished, idle;
		int from_x,from_y,to_x,to_y;
		double shift_x, shift_y, speed;
		double pos_x, pos_y;
		void calc();
		void move(double timeSinceLastFrame);

	};
}

#endif // ANIM_BASE_H_INCLUDED
