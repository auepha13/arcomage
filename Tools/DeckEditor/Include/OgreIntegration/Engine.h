/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	Engine.h
 * Desc: 	Engine Wrapper.
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
#ifndef _Engine_h_
#define _Engine_h_
#include <Singleton.h>

#include "EditorSystem.h"
#include "OgreSystem.h"
#include "OgreWidget.h"
namespace Arcomage {
	/**
	 * @brief Engine Wrapper for the UI Manager classes
	 */
	class Engine : public Arcomage::Singleton<Arcomage::Engine> {
		friend class Arcomage::Singleton<Arcomage::Engine>;
			public:
			Ogre::RenderWindow* getRenderWindow() {
				return OgreSystem::getInstance().getWidget(EditorSystem::getInstance().getRenderView())->getRenderWindow();
			}

			bool isSoundEnabled() {
				return false;
			}
	};
}

#endif