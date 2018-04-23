/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	DeckExporter.h
 * Desc: 	Deck Exporter Utility class, used to serialize Deck Data to be loaded
 *          by the game.
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
#ifndef _DeckExporter_h_
#define _DeckExporter_h_

#include <QtGUi>

class DeckExportWizard;
class EditorProject;

/**
 *
 */
enum DECK_APIVERSION{
	DECK_API_10,
	DECK_API_11
};

/**
 * @brief This class handles the serialization of deck data, it packs all required
 * information and media into a Deck File using the respective ProjectExporter
 * implementation.
 */
class DeckExporter : public QDialog {
		Q_OBJECT

public:
	DeckExporter(EditorProject* project, DeckExportWizard* wizard = 0, QWidget *parent = 0);

	/**
	 * Fully exports a project, using the given API version.
	 *
	 * @param api the API Version to use 
	 * @see DECK_APIVERSION
	 */ 
	void exportProject(DECK_APIVERSION api);
	
	/**
	 * Convenience function to get a better readable description from the API 
	 * enum.
	 *
	 * @param api the API Code 
	 * @return information on the API as a QString.
	 */ 
	QString toAPIString(DECK_APIVERSION api);

private:
	DeckExportWizard* wizard;
	EditorProject* project;
	void setup();

	QProgressBar *progress;
	QLabel *text;
};
#endif