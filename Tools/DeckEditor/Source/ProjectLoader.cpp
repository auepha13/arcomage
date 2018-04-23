/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	ProjectLoader.cpp
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
#include "ProjectLoader.h"
#include "ToolkitUtil.h"

// Arcomage Data
#include <DeckMetaData.h>
#include <DeckLoader.h>
#include <boost/filesystem.hpp>

#include "EditorProject.h"

#include <OgreResourceGroupManager.h>

// -----------------------------------------------------------------------------
ProjectLoader::ProjectLoader(const QString &fileName, QWidget *parent)
	: QDialog( parent, Qt::Tool |  Qt::CustomizeWindowHint | Qt::WindowTitleHint)
	, fileName(fileName) {
		setWindowTitle(tr("Opening ").append(fileName));

		// Build UI
		setup();
}

// -----------------------------------------------------------------------------
ProjectLoader::~ProjectLoader() {

}

// -----------------------------------------------------------------------------
void ProjectLoader::setup() {
	QVBoxLayout* layout = new QVBoxLayout(this);

	progress = new QProgressBar();
	text = new QLabel(tr("Opening..."));
	layout->addWidget(progress);
	layout->addWidget(text);

	setWindowModality(Qt::ApplicationModal);
	adjustSize();
}

// -----------------------------------------------------------------------------
EditorProject* ProjectLoader::load() {
	Arcomage::DeckMetaData* meta;
	try {
		meta = new Arcomage::DeckMetaData(Util::toStdString(fileName), true);


	//if(meta)
	//	ToolkitUtil::getInstance().notifyError(QString(meta->getMetaData("Name").c_str()));

		Arcomage::DeckLoader* loader;
		loader = new Arcomage::DeckLoader(meta, this);
		loader->load();

		return new EditorProject(meta, loader->getCards());
	} catch(std::exception& e) {
		ToolkitUtil::getInstance().notifyError("Error loading " + fileName);
	}

	return 0;
}
// -----------------------------------------------------------------------------
void ProjectLoader::notifyStart() {

}
// -----------------------------------------------------------------------------
void ProjectLoader::notifyProgress(const Arcomage::DeckProgress& t) {
	progress->setMaximum(t.total);
	progress->setMinimum(0);
	progress->setValue(t.current);
	text->setText(Util::toQString(t.message));
}

// -----------------------------------------------------------------------------
void ProjectLoader::notifyFinished() {
	//ToolkitUtil::getInstance().notifyError("Loaded");
}
