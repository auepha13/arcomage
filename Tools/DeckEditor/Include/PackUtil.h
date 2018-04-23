/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	PackUtil.h
 * Desc: 	Utility classes for Packing/Unpacking Deck Archives
 *
 * Date: 	01/2011
 *
 * Copyright (C) 2007 - 2011 Xography. <www.gatewayheaven.com>
 *
 * -----------------------------------------------------------------------------
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
 * -----------------------------------------------------------------------------
 */
#ifndef _PackUtil_h_
#define _PackUtil_h_
#include <Poco/AutoPtr.h>
#include <Poco/Zip/Decompress.h>
#include <Poco/Zip/ZipLocalFileHeader.h>
#include <Poco/Zip/ZipArchive.h>
#include <Poco/Path.h>
#include <Poco/File.h>
#include <Poco/Delegate.h>
#include <Poco/Zip/Compress.h>
#include <string>
#include "ToolkitUtil.h"

using Poco::Zip::ZipLocalFileHeader;
using Poco::AutoPtr;

// -----------------------------------------------------------------------------
// Quick Utility Class to Handle Decompression via Poco::Zip
class DecompressHandler {
public:
	DecompressHandler(){}

	~DecompressHandler(){}

	void onError(const void*, std::pair<const ZipLocalFileHeader, const std::string>& info) {
		ToolkitUtil::getInstance().exitError(Util::toQString(info.second));

	}

	void onOk(const void*, std::pair<const ZipLocalFileHeader, const Poco::Path>& info) {
	}

};

/**
 * @brief Package Utility class that can be used to unpack Deck Data or pack
 * an existing project into a .deck File.
 */ 
class PackUtil {
public:

	// -------------------------------------------------------------------------
	static void unpack(const std::string& filename, const std::string& dest) {
		Poco::Path outputDir(dest);

		std::ifstream in(filename.c_str(), std::ios::binary);
		Poco::Zip::Decompress c(in, outputDir);
		DecompressHandler handler;
		c.EError += Poco::Delegate<DecompressHandler, std::pair<const ZipLocalFileHeader, const std::string> >(&handler, &DecompressHandler::onError);
		c.EOk +=Poco::Delegate<DecompressHandler, std::pair<const ZipLocalFileHeader, const Poco::Path> >(&handler, &DecompressHandler::onOk);
		c.decompressAllFiles();
		c.EError -= Poco::Delegate<DecompressHandler, std::pair<const ZipLocalFileHeader, const std::string> >(&handler, &DecompressHandler::onError);
		c.EOk -=Poco::Delegate<DecompressHandler, std::pair<const ZipLocalFileHeader, const Poco::Path> >(&handler, &DecompressHandler::onOk);
	}

	// -------------------------------------------------------------------------
	static void packDir(const std::string& directory, const std::string& destFile) {
		std::ofstream out(destFile.c_str(), std::ios::binary);
		Poco::Zip::Compress c(out, true);
		DecompressHandler handler;
				Poco::File aFile(directory);
		if (aFile.exists()) {
			Poco::Path anEntry(directory);

			c.addRecursive(anEntry, Poco::Zip::ZipCommon::CL_MAXIMUM, true); // add root if we have more than one entry
		}
		c.close();
	}
};

#endif