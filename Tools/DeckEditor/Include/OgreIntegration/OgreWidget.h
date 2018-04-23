/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	OgreWidget.h
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
#ifndef _OgreWidget_h_
#define _OgreWidget_h_
#include <QWidget>
#include <OgrePrerequisites.h>

/**
 * @brief QWidget wrapping an Ogre RenderWindow into a QT Application.
 *
 * @note Heavily modified version of the QTOgreFrameworks' OgreWidget class.
 */ 
class OgreWidget : public QWidget {
	Q_OBJECT
public:
	OgreWidget(const QString& rwName, QWidget *parent = 0, bool doNotCreate = false, Qt::WFlags flags = 0);
	~OgreWidget();

	bool isInitialized();
	unsigned long wID();
	void deleteLater();

	Ogre::RenderWindow* getRenderWindow();

	QString getName() { return windowName; }

protected:
	QPaintEngine *paintEngine() const;
	void paintEvent(QPaintEvent* evt);
	void resizeEvent(QResizeEvent* evt);

private:
	Ogre::RenderWindow* renderWindow;

	QString windowName;
	bool initialized;

	//
	QTime* elapseTimer;
	long currentTime;
	long lastFrameTime;

	unsigned long winID;

	void setup(const QString& rwName);
};

#endif