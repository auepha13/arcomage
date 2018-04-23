/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	OgreSystem.h
 * Desc: 	Ogre Integration, this class provides a basic Ogre Framework
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
#ifndef _OgreSystem_h_
#define _OgreSystem_h_


#include <Ogre/AeonOgreSystem.h>
#include <OgreMaterial.h>
#include <Singleton.h>
#include <OgrePrerequisites.h>
#include <vector>
#include <OgreRenderQueueListener.h>

class OgreWidget;

/**
 * This class manages the Ogre root object and all Ogre widgets are REQUIRED
 * to register themselves with this manager in order to be updated.
 */ 
class OgreSystem : public Aeon::AeonOgreSystem, public Arcomage::Singleton<OgreSystem> ,public Ogre::RenderQueueListener {
	friend class Arcomage::Singleton<OgreSystem>;

public:

	void bootstrap();

	void setRSChoice(const std::string& rs);
	void shutdown();

	void registerWidget(OgreWidget* widget);
	void unregisterWidget(OgreWidget* widget);

	void registerMaterial(const Ogre::MaterialPtr& p);
	const Ogre::MaterialPtr& getMaterial();
	OgreWidget* getWidget(const std::string& name);

	void update();
	void setUIRenderingEnabled(bool enable) { renderUI = enable; }
protected:
	Ogre::RenderSystem* selectRenderSystem();
	std::string rendersys;

	/// Called from Ogre before a queue group is rendered.
	virtual void renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& skipThisInvocation);
	/// Called from Ogre after a queue group is rendered.
	virtual void renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation, bool& repeatThisInvocation);

private:
	std::vector<OgreWidget*> widgets;
	bool renderUI;
	Ogre::MaterialPtr ptr;

	long timeSinceLastUpdate;

	OgreSystem();
};
#endif