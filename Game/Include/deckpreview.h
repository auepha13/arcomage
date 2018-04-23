/*
 * Arcomage Tribute
 *
 * File:	deckpreview.h
 * Desc: 	Preview deck metadata from an .deck archive
 *
 * Date: 	07/2007
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

#ifndef DECKPREVIEW_H_INCLUDED
#define DECKPREVIEW_H_INCLUDED

#include <map>
#include "ArcomageForward.h"
#include <AeonCore.h>

namespace arcomage {

	class DeckPreview {
	public:
		DeckPreview(Ptr<Aeon::ZipFile> archive, const std::string &filename);
		const std::string& getMetaData(const std::string& entry);

	private:
		std::map<const std::string, std::string> meta;
	};

}
#endif // DECKPREVIEW_H_INCLUDED
