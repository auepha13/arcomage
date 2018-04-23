/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	OgreWidget.cpp
 * Desc:	Custom QT Widget wrapping an OGRE RenderWindow
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
#include "OgreWidget.h"
#include "OgreSystem.h"
#include "ToolkitUtil.h"

#include <OgreRoot.h>
#include <OgreString.h>
#include <OgreRenderWindow.h>

#include <sstream>
#include <QTime>

#include <UI/UIManager.h>

// -----------------------------------------------------------------------------
OgreWidget::OgreWidget(const QString& rwName,  QWidget *parent, bool doNotCreate /* =f alse*/, Qt::WFlags flags) 
	: QWidget(parent, flags), renderWindow(0), windowName(rwName), initialized(false), lastFrameTime(0), winID(0) {
	QPalette colourPalette = palette();
	colourPalette.setColor(QPalette::Active, QPalette::WindowText, Qt::black);
	colourPalette.setColor(QPalette::Active, QPalette::Window, Qt::black);
	setPalette(colourPalette);

	if(!doNotCreate) {
		elapseTimer = new QTime();
		elapseTimer->start();
		this->setup(rwName);

		lastFrameTime = elapseTimer->elapsed();
	}

	winID = (unsigned long)winId();
}

// -----------------------------------------------------------------------------
OgreWidget::~OgreWidget() {
	renderWindow = 0;
	delete renderWindow;

	Ogre::Root::getSingleton().detachRenderTarget(Util::toStdString(windowName));
}

// -----------------------------------------------------------------------------
unsigned long OgreWidget::wID() {
	return winID;
};

// -----------------------------------------------------------------------------
void OgreWidget::deleteLater() {
	//context->leave();
	OgreSystem::getInstance().unregisterWidget(this);
	Ogre::Root::getSingleton().detachRenderTarget(Util::toStdString(windowName));
	renderWindow = 0;
	delete renderWindow;

	QWidget::deleteLater();
}

// -----------------------------------------------------------------------------
void OgreWidget::setup(const QString& rwName) {
	Ogre::Root& root = Ogre::Root::getSingleton();

	Ogre::NameValuePairList miscParams;
	miscParams["FSAA"] = "8";
	miscParams["vsync"] = "true";

	//These attributes are the same as those use in a QGLWidget
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);
	setAttribute(Qt::WA_NoBackground);
	/*
	QWidget::grabKeyboard ();
	QWidget::setMouseTracking (true);
	//Accept input focus
	setFocusPolicy(Qt::StrongFocus);
	*/
	setContextMenuPolicy( Qt::PreventContextMenu );

	setFocusPolicy(Qt::WheelFocus);
	//Parameters to pass to Ogre::Root::createRenderWindow()
	miscParams["useNVPerfHUD"] = "false";

	//If the user passed in any parameters then be sure to copy them into our own parameter set.
	//NOTE: Many of the parameters the user can supply (left, top, border, etc) will be ignored
	//as they are overridden by Qt. Some are still useful (such as FSAA).


	//The external windows handle parameters are platform-specific
	std::stringstream externalWindowHandleParams;



#if defined(Q_WS_WIN)
	//positive integer for W32 (HWND handle) - According to Ogre Docs
	externalWindowHandleParams << (unsigned long)winId();
#endif

#if defined(Q_WS_X11)
	//poslong:posint:poslong:poslong (display*:screen:windowHandle:XVisualInfo*) for GLX - According to Ogre Docs
	QX11Info info = x11Info();
	externalWindowHandleParams << info.display();
	externalWindowHandleParams << ":";
	externalWindowHandleParams << info.screen();
	externalWindowHandleParams << ":";
	externalWindowHandleParams << (unsigned long)winId();
	//externalWindowHandleParams += ":";
	//externalWindowHandleParams += Ogre::StringConverter::toString((unsigned long)(info.visual()));
#endif

	//Add the external window handle parameters to the existing params set.
#if defined(Q_WS_WIN)		
	miscParams["externalWindowHandle"] = externalWindowHandleParams.str();
#endif

#if defined(Q_WS_X11)
	miscParams["parentWindowHandle"] = externalWindowHandleParams.str();
#endif

	//Finally create our window.
	try {
		renderWindow = Ogre::Root::getSingletonPtr()->createRenderWindow(Util::toStdString(rwName), width(), height(), false, &miscParams);
		initialized = true;
	} catch(Ogre::InternalErrorException& e) {
		ToolkitUtil::getInstance().exitError(e.what());
	} 

	if(initialized) {
		OgreSystem::getInstance().registerWidget(this);
		//context->enter(this);
	}
}

// -----------------------------------------------------------------------------
QPaintEngine *OgreWidget:: paintEngine() const {
	return 0;
}

// -----------------------------------------------------------------------------
void OgreWidget::paintEvent(QPaintEvent* evt) {
	if(Ogre::Root::getSingleton().isInitialised()) {
		
		Ogre::Root::getSingleton()._fireFrameStarted();
		

		if(renderWindow) {
			renderWindow->update();
		}
		
		Ogre::Root::getSingleton()._fireFrameRenderingQueued();
		currentTime = elapseTimer->elapsed();

		/*
		if(context != 0) 
			context->updated((currentTime - lastFrameTime) / 1000.0f);
		*/ 

		Ogre::Root::getSingleton()._fireFrameEnded();
		lastFrameTime = currentTime;
	}
}

// -----------------------------------------------------------------------------
Ogre::RenderWindow* OgreWidget::getRenderWindow() {
	return renderWindow;
}

// -----------------------------------------------------------------------------
void OgreWidget::resizeEvent(QResizeEvent* evt)
{
	if(renderWindow)
	{
		renderWindow->resize(width(), height());
		renderWindow->windowMovedOrResized();

		for(int ct = 0; ct < renderWindow->getNumViewports(); ++ct)
		{
			Ogre::Viewport* pViewport = renderWindow->getViewport(ct);
			Ogre::Camera* pCamera = pViewport->getCamera();
			pCamera->setAspectRatio(
				static_cast<Ogre::Real>(pViewport->getActualWidth()) 
				/ static_cast<Ogre::Real>(pViewport->getActualHeight())
				);
		}
	}
}

// -----------------------------------------------------------------------------
bool OgreWidget::isInitialized() {
	return initialized;
}
