/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	ToolkitUtil.h
 * Desc: 	A Set of common utility functions.
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
#ifndef _ToolkitUtil_h_
#define _ToolkitUtil_h_
#include <Singleton.h>
#include <QString>
#include <QMessageBox>
#include <string>
#include <boost/filesystem.hpp>


namespace Util {
	
	/**
	 * Converts a Qtring into a STL String.
	 */
	inline std::string toStdString(const QString& str) {
		return str.toLocal8Bit().data();
	}

	/**
	 * Converts a STL string into a QString.
	 */
	inline QString toQString(const std::string& str) {
		return QString(str.c_str());
	}

	/**
	 * Extracts the filename out of a given path.
	 */
	inline std::string extractFilename(const std::string& path) {
		return boost::filesystem::path(path).filename();
	}
}

/**
 * @brief Utility Class, provides convenience-methods to notify the user of
 * events, as well as an emergency exit function.
 */
class ToolkitUtil : public Arcomage::Singleton<ToolkitUtil> {
	friend class Arcomage::Singleton< ToolkitUtil >;

public:
	void notifyError(const QString &msg);
	void exitError(const QString &msg);
	void notify(const QString &msg);
	
private:
	ToolkitUtil(){}
};

#endif