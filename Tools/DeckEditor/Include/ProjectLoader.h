/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	ProjectLoader.h
 * Desc: 	A Project Loader, provides a Factory for Editor Projects.
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
#ifndef _ProjectLoader_h_
#define _ProjectLoader_h_
#include <QDialog>
#include <QtGui> 
#include <LoadListener.h>
#include <ArcomageForward.h>

class EditorProject;

/**
 * @brief Loads & Parses existing Data and instantiates new Editor Projects from the 
 * given file.
 */ 
class ProjectLoader : public QDialog, public Arcomage::LoadListener<Arcomage::DeckProgress> {
	Q_OBJECT

public:
	ProjectLoader(const QString &fileName, QWidget *parent);
	~ProjectLoader();

	/**
	 * Attempt to parse a the given file (passed upon construction), allocate
	 * resources and set up required paths and the Project itself.
	 *
	 * @return A ready-to-use Project for the Editor.
	 */ 
	EditorProject* load();

	/**
	 * Callback for the LoadListener Interface, this method is called upon startup of
	 * the parsing process
	 */ 
	virtual void notifyStart();

	/**
	 * Callback for the LoadListener Interface, as soon as the parser finished  
	 * reading the data of a Card, this method gets called.
	 * @param t Set of data containing information about the current progress.
	 */ 
	virtual void notifyProgress(const Arcomage::DeckProgress& t);

	/**
	 * Callback for the LoadListener Interface, when the parser has finished
	 * reading the deck data.
	 */ 
	virtual void notifyFinished();

private:
	QString fileName;
	void setup();

	QProgressBar *progress;
	QLabel *text;

};


#endif