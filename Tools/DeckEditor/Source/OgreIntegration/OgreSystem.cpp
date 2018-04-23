/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	OgreSystem.cpp
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
#include "OgreSystem.h"
#include "RendersystemSelection.h"
#include "ToolkitUtil.h"
#include "Exception.h"
#include <UI/UIManager.h>
#include "OgreWidget.h"
#include <OgreMaterialManager.h>
#include <AeonPlatform.h>
#include <algorithm> 

// ----------------------------------------------------------------------------
OgreSystem::OgreSystem() : timeSinceLastUpdate(0), renderUI(false) {

}

// ----------------------------------------------------------------------------
void OgreSystem::bootstrap() {
	std::string plugins;

	plugins = (AEON_PLATFORM == AEON_WIN32) 
		?  (OGRE_DEBUG_MODE == 1 ? "EditorPlugins.Windows_d.conf" : "EditorPlugins.Windows.conf" )
		:  ((AEON_PLATFORM == AEON_MACOS) 
			? "EditorPlugins.Mac.conf" 
			: "EditorPlugins.Linux.conf");

	/*
		// Load minimal set of resources (Fonts, GUI, ...)
	OgreSystem::loadResources(Aeon::ResourceRepositoryManager::getInstance().getBasePath(), 
		Aeon::ResourceRepositoryManager::getInstance().getResourcePath("Ogre-Common"));
	*/
	try  {
		AeonOgreSystem::initialize("Editor/"+plugins, 
			"Editor/Renderer.conf",
			"Editor/Editor.log");
		
		OgreSystem::loadResources("", "Editor/EditorResources.conf");
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	} catch(Ogre::Exception& e) {
		ToolkitUtil::getInstance().exitError(e.what());
	}

}

// ----------------------------------------------------------------------------
void OgreSystem::shutdown() {
	root->saveConfig();
}

// ----------------------------------------------------------------------------
void OgreSystem::setRSChoice(const std::string& rs) {
	rendersys = rs;
}

// -----------------------------------------------------------------------------
OgreWidget* OgreSystem::getWidget(const std::string& name) {
	for (std::vector<OgreWidget*>::iterator it = widgets.begin();
		it != widgets.end();
		++it){
			if(Util::toStdString((*it)->getName()) == name)
				return *it;
	}
	return 0;
}

// ----------------------------------------------------------------------------
Ogre::RenderSystem* OgreSystem::selectRenderSystem() {
	rendersys = "";
	//RendersystemSelection rs(root->getAvailableRenderers());

	// We'll override this for now until the DirectX issues are fixed.
	if(root->getAvailableRenderers().size() > 0) {
		return root->getRenderSystemByName("OpenGL Rendering Subsystem");
	}

	/*
	if(rs.exec() == QDialog::Accepted) {
		return root->getRenderSystemByName(rendersys);	
	} else {
		return 0;
	}
	*/
}
// ----------------------------------------------------------------------------
void OgreSystem::registerWidget(OgreWidget* widget) {
	widgets.push_back(widget);
}
// ----------------------------------------------------------------------------
void OgreSystem::unregisterWidget(OgreWidget* widget) {
	auto it = widgets.begin();

	while(!widgets.empty() && it != widgets.end()) {
		if((*it) == 0 || (*it)->wID() == widget->wID())
			widgets.erase(it++);
		else
			it++;
	}

}
// -----------------------------------------------------------------------------
void OgreSystem::update() {
	foreach(OgreWidget* w, widgets) {
		// used to prevent interference with QT's paint method.
		if(!w->paintingActive() && w != 0)
			w->update();
	}

}
// -------------------------------------------------------------------------
void OgreSystem::renderQueueStarted(
	Ogre::uint8 queueGroupId, 
	const Ogre::String& invocation, 
	bool& skipThisInvocation) {
		if (queueGroupId == Ogre::RENDER_QUEUE_OVERLAY 
			&& root->getRenderSystem()->_getViewport()->getOverlaysEnabled() && renderUI) {
				Arcomage::UI::UIManager::getInstance().update();
		}
}

// -------------------------------------------------------------------------
void OgreSystem::renderQueueEnded(
	Ogre::uint8 queueGroupId, 
	const Ogre::String& invocation, 
	bool& repeatThisInvocation) {
}
// -----------------------------------------------------------------------------
void OgreSystem::registerMaterial(const Ogre::MaterialPtr& p) {
	ptr = p;
}

// -----------------------------------------------------------------------------
const Ogre::MaterialPtr& OgreSystem::getMaterial() {
	return ptr;
}


