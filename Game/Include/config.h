/*
 * Arcomage Tribute
 *
 * File: config.h
 * Desc: configuration class
 *
 * Date: 05/2007
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

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "global.h"

namespace arcomage {
	class Config : public Singleton<Config> {
		friend class Singleton<Config>;
		// -------------------------------------------------------------------------
		// public
	public:
		// Methods
		~Config()
		{
		};
		static Config* getInstance()
		{
			return Singleton<Config>::getInstance();
		}

		int readInteger(const char* child,
			const char* attribute,
			const char* file);

		const char* readString(const char* child,
			const char* attribute,
			const char* file);
		// -------------------------------------------------------------------------
		// proctected:
	protected:
		Config() : Singleton<Config> ()
		{
		}
	};
}


#endif // CONFIG_H_INCLUDED
