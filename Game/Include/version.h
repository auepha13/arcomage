/*
 * Arcomage Tribute
 *
 * File: 	version.h
 * Desc: 	For easier versioning
 *
 * Date: 	12/2008
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
#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion {

	//Date Version Types
	static const char DATE[] = "10";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2012";
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";

	//Standard Version Type
	static const long MAJOR = 0;
	static const long MINOR = 3;
	static const long BUILD = 5;
	static const long REVISION = 0;

	//Miscellaneous Version Types
	// disabled
	// static const long BUILDS_COUNT = 940;
	#define RC_FILEVERSION 0,3,5,0
	#define RC_FILEVERSION_STRING "0, 3, 5, 0\0"
	static const char FULLVERSION_STRING[] = "0.3.5.0";

	//These values are to keep track of your versioning state, don't modify them.
	// disabled
	//static const long BUILD_HISTORY = 22;


}
#endif //VERSION_h
