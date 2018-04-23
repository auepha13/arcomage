/*
 * Arcomage Tribute
 *
 * File: 	utility.cpp
 * Desc: 	Utility class, providing functions for logging etc
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
#include "utility.h"

#ifdef _MSC_VER
	#include <time.h>
	#include <sys/types.h>
	#include <sys/timeb.h>
#endif

namespace arcomage {

	// -------------------------------------------------------------------------
	// log a message (one line) to a file
	void Utility::logMessage(const char* filename, const char* msg)
	{
		char timestr[20];
		time_t seconds = time(0);
		struct tm* ptm = localtime(&seconds);

		sprintf(timestr, "%04i-%02i-%02i %02i:%02i:%02i",
			(int)ptm->tm_year+1900,
			(int)ptm->tm_mon+1,
			(int)ptm->tm_mday,
			(int)ptm->tm_hour,
			(int)ptm->tm_min,
			(int)ptm->tm_sec);

		FILE* logfile;
		logfile=fopen(filename, "a");
		if (!logfile) printf("[%s] Cannot open %s", timestr, filename);
		fprintf(logfile, "[%s]: %s\n", timestr, msg);
		std::cout << "[" << timestr << "]: " << msg << std::endl;

		fclose(logfile);
	}

	// -------------------------------------------------------------------------
	// quit the program and log a string to error.log
	void Utility::exitError(const char* msg)
	{
		std::cerr << "ERROR: " <<  msg << " (Logfile saved: arcomage.log)" <<
			std::endl;

		logMessage("arcomage.log",
			std::string("* Fatal Error occured: ")
			.append(msg).c_str());
		std::exit(0);
	}
	std::string Utility::getFileExtension(std::string path)
	{
		int index;
		if((index = path.find_last_of(".")) != -1)
			return path.substr(index);
		return "";
	}

	// -------------------------------------------------------------------------
	// split a string by a specific delimiter and return a vector filled with the parts
	void Utility::Tokenize(const std::string& str,
		std::vector<std::string>& token_vec,
		const std::string& delimiters = " ")
	{
		using namespace std;
		using namespace boost;
		boost::algorithm::split_regex( token_vec, str,
			boost::regex( delimiters.c_str() ) ) ;
	}

}
