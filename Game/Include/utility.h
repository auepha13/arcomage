/*
 * Arcomage Tribute
 *
 * File: utility.h
 * Desc: Utility Class
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
#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include "singleton.h"
#include <sstream>
#include <string.h>
#include <vector>
#include <iostream>
#include <boost/algorithm/string/regex.hpp>
#include <boost/regex.hpp>

namespace arcomage {

	template <class T>
	inline std::string to_string(const T& t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}

	class Utility : public Singleton<Utility> {
		friend class Singleton<Utility>;
		// -------------------------------------------------------------------------
		// public
	public:
		// Methods
		~Utility()
		{
		};
		static Utility* getInstance()
		{
			return Singleton<Utility>::getInstance();
		}
		void logMessage(const char* filename, const char* msg);
		void exitError(const char* msg);
		void exitError(const std::string& msg)
		{
			exitError(msg.c_str());
		}

		void Tokenize(const std::string& str,
			std::vector<std::string>& token_vec,
			const std::string& delimiters);
		std::string getFileExtension(std::string path);

		// -------------------------------------------------------------------------
		// protected
	protected:
		Utility() : Singleton<Utility> ()
		{
		}
	};
}

#endif // UTILITY_H_INCLUDED
