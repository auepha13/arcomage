/*
 * Arcomage Tribute
 *
 * File: timer.h
 * Desc: Timer Class (from Lazyfoo productions)
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
#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

namespace arcomage {
	class Timer {
	private:
		//The clock time when the timer started
		int startTicks;

		//The ticks stored when the timer was paused
		int pausedTicks;

		//The timer status
		bool paused;
		bool started;

	public:
		//Initializes variables
		Timer()
		{
			//Initialize the variables
			startTicks = 0;
			pausedTicks = 0;
			paused = false;
			started = false;
		}

		//The various clock actions
		void start()
		{
			//Start the timer
			started = true;

			//Unpause the timer
			paused = false;

			//Get the current clock time
			startTicks = SDL_GetTicks();
		}

		void stop()
		{
			//Stop the timer
			started = false;

			//Unpause the timer
			paused = false;
		}

		void pause()
		{
			//If the timer is running and isn't already paused
			if ((started == true) && (paused == false)) {
				//Pause the timer
				paused = true;

				//Calculate the paused ticks
				pausedTicks = SDL_GetTicks() - startTicks;
			}
		}

		void unpause()
		{
			//If the timer is paused
			if (paused == true) {
				//Unpause the timer
				paused = false;

				//Reset the starting ticks
				startTicks = SDL_GetTicks() - pausedTicks;

				//Reset the paused ticks
				pausedTicks = 0;
			}
		}

		//Gets the timer's time
		int get_ticks()
		{
			//If the timer is running
			if (started == true) {
				//If the timer is paused
				if (paused == true) {
					//Return the number of ticks when the timer was paused
					return pausedTicks;
				} else {
					//Return the current time minus the start time
					return SDL_GetTicks() - startTicks;
				}
			}

			//If the timer isn't running
			return 0;
		}

		//Checks the status of the timer
		bool is_started()
		{
			return started;
		}

		bool is_paused()
		{
			return paused;
		}
	};

}

#endif // TIMER_H_INCLUDED
