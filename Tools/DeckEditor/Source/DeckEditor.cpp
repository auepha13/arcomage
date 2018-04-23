/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	DeckEditor.cpp
 * Desc: 	Deck Editor Main class, serving as Mainwindow
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
#include "DeckEditor.h"
#include "OgreWidget.h"
#include "OgreSystem.h"
#include <ConfigurationManager.h>
#include <ResourceManager.h>
#include <UIManager.h>
#include <QTimer>
#include <QDesktopWidget>
#include <Ogre.h>
#include <QFileDialog>
#include <QObject>

#include "ProjectLoader.h"
#include "ProjectWizard.h"
#include "CardEditor.h"
#include "DeckExportWizard.h"
#include "EditorProject.h"
#include "ToolkitUtil.h"
#include "AboutDialog.h"
#include "MetaDataEditor.h"

#include <stdlib.h>
#include <QDesktopServices>

std::string DeckEditor::Version = "v0.3.3.0pre2";
// -----------------------------------------------------------------------------
std::string DeckEditor::VersionString = "Arcomage Tribute Deck Editor "
										+ Version 
										+ " (Build Date: " 
										+ std::string(__DATE__) 
										+ ")";

// -----------------------------------------------------------------------------
DeckEditor::DeckEditor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags), ogreSystem(OgreSystem::getInstance()), 
	widget(0), 
	timer(0),
	editor(0),
	metaEditor(0),
	remindLegacyDeck(true),
	documentChanged(false),
	isProject(false)
{
	ui.setupUi(this);

	// Bootstrap Ogre3D
	ogreSystem.bootstrap();

	// Prepare Configuration
	Arcomage::ConfigurationManager::getInstance().setBasePath("Data");
	Arcomage::ConfigurationManager::getInstance().loadConfiguration("Editor/Resource.xml");
	
	Ogre::Root* root = Ogre::Root::getSingletonPtr();

	Ogre::SceneManager* sceneMngr = root->createSceneManager(Ogre::ST_GENERIC, "root");
	sceneMngr->addRenderQueueListener(&OgreSystem::getInstance());

	this->setWindowTitle(tr("Arcomage Tribute Deck Editor"));
	timer = new QTimer(this);
	timer->start(1000.0f / 30);
	connect(timer, SIGNAL(timeout()), this, SLOT(tick()));

	// Center application
	QRect available_geom = QDesktopWidget().availableGeometry();
	QRect current_geom = frameGeometry();
	setGeometry(available_geom.width() / 2 - current_geom.width() / 2,
		available_geom.height() / 2 - current_geom.height() / 2,
		current_geom.width(),
		current_geom.height()
		);

	ui.browser->setUrl(QUrl("Editor/HTML/index.html"));

	// Connect everything
	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(loadDeck()));
	connect(ui.actionAbout_Arcomage_Deck_Editor, SIGNAL(triggered()), this, SLOT(about()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(exitProgram()));
	connect(ui.actionReport_Bug, SIGNAL(triggered()), this, SLOT(reportBug()));
	connect(ui.actionProject_Website, SIGNAL(triggered()), this, SLOT(projectWebsite()));
	connect(ui.actionExport, SIGNAL(triggered()), this, SLOT(exportDeck()));
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(saveProject()));
	connect(ui.actionNew , SIGNAL(triggered()), this, SLOT(newProject()));
	connect(ui.actionSubmit_your_Deck_online, SIGNAL(triggered()),this,SLOT(uploadDeck()));

}
// -----------------------------------------------------------------------------
DeckEditor::~DeckEditor()
{

}

// -----------------------------------------------------------------------------
void DeckEditor::notifyDocumentChanged() {
	if(editor)
		this->setWindowTitle(tr("Arcomage Tribute Deck Editor - %1 (Modified)").arg(editor->getProject()->getFilename().c_str()));

	documentChanged = true;
}

// -----------------------------------------------------------------------------
void DeckEditor::reportBug() {
	QDesktopServices::openUrl(QUrl("http://redmine.gatewayheaven.com/projects/arcomage/issues", QUrl::TolerantMode));

}

// -----------------------------------------------------------------------------
void DeckEditor::uploadDeck() {
	QDesktopServices::openUrl(QUrl("http://arcomage.gatewayheaven.com/editor/submit-deck/", QUrl::TolerantMode));

}

// -----------------------------------------------------------------------------
void DeckEditor::projectWebsite() {
	QDesktopServices::openUrl(QUrl("http://www.gatewayheaven.com/projects/arcomage/", QUrl::TolerantMode));
}

// -----------------------------------------------------------------------------
void DeckEditor::about() {
	AboutDialog dlg;
	dlg.exec();
}
// -----------------------------------------------------------------------------
void DeckEditor::exitProgram() {
	qApp->exit();
}

// -----------------------------------------------------------------------------
void DeckEditor::tick() {
	 ogreSystem.update();
}

// -----------------------------------------------------------------------------
void DeckEditor::closeEvent(QCloseEvent *event) {

	if (documentChanged) {
		QMessageBox msgBox;
		msgBox.setText("The document has been modified.");
		msgBox.setInformativeText("Do you want to save your changes?");
		msgBox.setIcon(QMessageBox::Question);
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		int ret = msgBox.exec();

		if(ret == QMessageBox::Save) {
			if(editor) {
				if(editor->getProject()) {
					DeckExportWizard wizard(lastFile, editor->getProject(), this);
					wizard.exec();
				}

				editor->releaseEditorResources();
			}
			event->accept();
		} else if(ret == QMessageBox::Discard) {
			if(editor) {
				editor->releaseEditorResources();
			}
			event->accept();
		}	 else {
			event->ignore();
		}
	} else {
		
		if(editor) {
			editor->releaseEditorResources();
		}

		QWidget::closeEvent(event);
	}

}

// -----------------------------------------------------------------------------
void DeckEditor::loadDeck() {
	QString fileName;
	bool _continue = false;
	fileName = QFileDialog::getOpenFileName(this,
		tr("Open Deck File"), "Data/Decks", tr("Deck Files (*.deck)"));

	if(!fileName.isEmpty()) {
		documentChanged = false;

		ProjectLoader* loader = new ProjectLoader(fileName, this);

		loader->show();
		EditorProject* project = loader->load();

		if(project) {
			project->prepare();
			lastFile = fileName;
			isProject = false;
			_continue = true;
		}

		if(!editor && !metaEditor && _continue) {
			this->setWindowTitle(tr("Arcomage Tribute Deck Editor - %1").arg(
				Util::extractFilename(Util::toStdString(fileName)).c_str()));

			editor = new CardEditor(project, this, this);
			metaEditor = new MetaDataEditor(project, this, this);

			ui.tabWidget->addTab(editor,
				QIcon(":/DeckEditor/Resources/Icons/card.png"),
				"&Card Editor");
			ui.tabWidget->setCurrentWidget(editor);

			editor->loadEditorResources();

			ui.tabWidget->addTab(metaEditor,
				QIcon(":/DeckEditor/Resources/Icons/information-frame.png"),
				"Deck &Metadata");

			//ui.actionClose_Project->setEnabled(true);
			ui.actionExport->setEnabled(true);
			/*
			ui.actionSave->setEnabled(true);
			ui.actionSave_Project_as->setEnabled(true);
			*/
		} else {
		// If there already exists a Project, we're resetting everything
			if(_continue) {
				metaEditor->setProject(project);
				editor->setProject(project);
			}
		}

		loader->close();	
		delete loader;

	}	
}

/*
if(project->isLegacyDeck() && remindLegacyDeck) {
	QMessageBox msgBox;
	msgBox.setText(tr("This Deck was created with an outdated version of the Deck Editor.\n"
		"The Deck will be opened in Compatibility mode with Editing limited to Cards only.\n"
		"\n"
		"You will need to convert or export this Deck to a more recent Version\n"
		"in order to be able to edit Scripts and Templates."));
	msgBox.setWindowTitle(tr("Outdated Deck Version"));
	msgBox.setIcon(QMessageBox::Warning);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setDefaultButton(QMessageBox::Ok);

	QCheckBox dontPrompt(QObject::tr("Do not display this Warning again"), &msgBox);

	// HACK: BLOCKING SIGNALS SO QMessageBox WON'T CLOSE
	dontPrompt.blockSignals(true);

	msgBox.addButton(&dontPrompt, QMessageBox::ActionRole);

	//QAbstractButton* pOK = (QAbstractButton*)msgBox.addButton(QMessageBox::Ok);
	msgBox.exec();

	if ( dontPrompt.checkState() == Qt::Checked ) {
		remindLegacyDeck = false;
	}
}
*/
// -----------------------------------------------------------------------------
void DeckEditor::exportDeck() {
	if(editor && editor->getProject()) {
		DeckExportWizard wizard(lastFile, editor->getProject(), this);
		wizard.exec();
	}
}

// -----------------------------------------------------------------------------
void DeckEditor::saveProject() {
	if(isProject) {
		// project.saveChanges
	} else {
		ProjectWizard wizard(editor->getProject());
		wizard.exec();
	}
}

// -----------------------------------------------------------------------------
void DeckEditor::newProject() {
	if(!documentChanged) {
		EditorProject* proj = new EditorProject(); 
		ProjectWizard wizard(proj);
		wizard.exec();
		//wizard->createNew();
	}
}

// -----------------------------------------------------------------------------
void DeckEditor::saveProjectAs() {

}

// -----------------------------------------------------------------------------
void DeckEditor::closeCurrentProject() {

}