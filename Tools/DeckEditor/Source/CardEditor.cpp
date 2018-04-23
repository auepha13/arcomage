/*
 * Arcomage Tribute Deck Editor
 * -----------------------------------------------------------------------------
 * File: 	CardEditor.cpp
 * Desc: 	Custom OgreWidget, enabling the user to edit a deck of cards.
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
#include "CardEditor.h"
#include "OgreWidget.h"
#include "OgreSystem.h"
#include "EditorProject.h"
#include "ToolkitUtil.h"
#include "AtlasGenerator.h"

#include <Utility.h>
#include <ConfigurationManager.h>
#include <ResourceManager.h>
#include <UIManager.h>
#include <Ogre.h>

#include <Rocket/Core/Factory.h>
#include <QInputDialog>
#include <QFileDialog>
#include <QDesktopServices>
#include "EditorSystem.h"

// -----------------------------------------------------------------------------
CardEditor::CardEditor(EditorProject* project, DeckEditor* parentEditor, QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags), 
		EditorWidget(project, parentEditor), 
		widget(0), 
		cards(project->getCards()), 
		current(0), 
		hasChanged(false),
		notified(false),
		currentItem(0),
		cardCount(cards.size()),
		rsError(false) {

		ui.setupUi(this);

		// We're trying to create a 3D Render Preview. If this fails, the user
		// will still be able to edit stuff, but can't preview changes.
		try {
			// Create Editor RenderView
			widget = new OgreWidget(Util::toQString(EditorSystem::getInstance().getRenderView()), ui.ogreWidget);

			widget->setBaseSize(QSize(288,384));
			widget->setFixedWidth(288);
			widget->setFixedHeight(384);
			widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
			widget->setFocusPolicy(Qt::NoFocus);

			ui.ogreWidget->setAttribute(Qt::WA_PaintOnScreen);
			ui.ogreWidget->setAttribute(Qt::WA_NoSystemBackground);
			ui.ogreWidget->setAttribute(Qt::WA_NoBackground);
			ui.innerLayout->addWidget(widget, 1, 1);

			// We need a camera and Viewport in order to display anything
			Ogre::Camera* camera = Ogre::Root::getSingletonPtr()->getSceneManager("root")->createCamera("PlayerCam");
			Ogre::Viewport* viewport = static_cast<OgreWidget*>(widget)->getRenderWindow()->addViewport(camera);
			camera->setAspectRatio(
				Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));

			// Initialize UI & associated Managers
			Arcomage::UI::UIManager::getInstance().bootstrap();
		
			// Preload required Editor Fonts
			Arcomage::ResourceManager::getInstance().preloadResources(
				Arcomage::ConfigurationManager::getInstance().getPath("Fonts")+"/fonts.xml",
				/* unused, Music */ "", 
				/* unused, Sound effects */ "");
			
		} catch (Ogre::Exception& e) {
			rsError = true; 
			widget = new OgreWidget("errorwidget", ui.ogreWidget, true);
			ToolkitUtil::getInstance().notifyError(e.what());
		}

		populateTree();
		this->connectUI();
}

// -----------------------------------------------------------------------------
CardEditor::~CardEditor() {

}
// -----------------------------------------------------------------------------
void CardEditor::connectUI() {
	connect(ui.cardList,SIGNAL(clicked(const QModelIndex&)), this, SLOT(treeItemClicked(const QModelIndex&)));
	connect(ui.buttonReset, SIGNAL(clicked()), this, SLOT(resetChanges()));
	connect(ui.buttonApply, SIGNAL(clicked()), this, SLOT(applyChanges()));
	connect(ui.dropDownCardType, SIGNAL(activated(int)),this,SLOT(changeCardType()));
	connect(ui.textCardCaption, SIGNAL(textChanged()), this, SLOT(captionChanged()));
	connect(ui.spinRequirements, SIGNAL(valueChanged(int)), this, SLOT(requirementsChanged()));
	connect(ui.editCardName, SIGNAL(textChanged(QString)), this, SLOT(nameChanged()));

	// Validate Values on change
	connect(ui.tableResources, SIGNAL(itemChanged( QTableWidgetItem* )), this, SLOT(validateValues()));
	connect(ui.tableModifiers, SIGNAL(itemChanged( QTableWidgetItem* )), this, SLOT(validateValues()));

	// Connect Change Listener
	connect(ui.editCardName, SIGNAL(editingFinished()), this, SLOT(somethingChanged()));
	connect(ui.spinDamageOpponent, SIGNAL(valueChanged(int)), this, SLOT(somethingChanged()));
	connect(ui.spinDamageSelf, SIGNAL(valueChanged(int)), this, SLOT(somethingChanged()));
	connect(ui.checkAddTurn, SIGNAL(clicked()), this, SLOT(somethingChanged()));
	connect(ui.checkDiscard, SIGNAL(clicked()), this, SLOT(somethingChanged()));
	connect(ui.checkNotDiscardable, SIGNAL(clicked()), this, SLOT(somethingChanged()));
	connect(ui.tableResources, SIGNAL(itemDoubleClicked( QTableWidgetItem* )), this, SLOT(somethingChanged()));
	connect(ui.tableModifiers, SIGNAL(itemDoubleClicked( QTableWidgetItem* )), this, SLOT(somethingChanged()));
	connect(ui.buttonRemoveCard, SIGNAL(clicked()), this, SLOT(removeCard()));
	connect(ui.buttonAddCard, SIGNAL(clicked()), this, SLOT(addCard()));
	connect(ui.buttonOpenImage, SIGNAL(clicked()), this, SLOT(selectImage()));
}

// -----------------------------------------------------------------------------
void CardEditor::populateTree() {
	// If we're simply loading a new Project, refresh the view
	if(!ui.cardList->size().isEmpty()) {
		ui.cardList->clear();
		reset();
	}

	// Populate List
	int i = 0;
	foreach(Arcomage::Card* c, cards) {
		addCardToList(c, i);
		i++;
	}

	ui.cardList->setSortingEnabled(true);
	ui.cardList->sortItems(0, Qt::AscendingOrder);
	
	// Adjust header
	ui.cardList->header()->resizeSection(0, 20);
	ui.cardList->header()->resizeSection(1, 20);
	ui.cardList->header()->setResizeMode(QHeaderView::Fixed);

	Rocket::Core::Factory::ClearStyleSheetCache();

	Arcomage::UI::UIManager::getInstance().setActiveUI(
		"Editor/Resources", 
		"Editor3D.uidef",
		true);

	Arcomage::UI::UIManager::getInstance().setWindowExtents(widget->geometry().width(), widget->geometry().height());
	OgreSystem::getInstance().setUIRenderingEnabled(true);

	// Only Display the first card if there exist any 
	if(!cards.empty()) {
		ui.cardList->setCurrentIndex(ui.cardList->rootIndex());
		current = cards.at(0);
		currentItem = ui.cardList->topLevelItem(0);
		display(current);
		updateCardDisplay(current);
	}




}

// -----------------------------------------------------------------------------
void CardEditor::setProject(EditorProject* project) {
	this->_project = project;
	cards = project->getCards();
	populateTree();
}

// -----------------------------------------------------------------------------
void  CardEditor::somethingChanged() {
	if(!notified) {
		parentEditor->notifyDocumentChanged();
		notified = true;
	}

	hasChanged = true;
	ui.buttonApply->setEnabled(true);
	ui.buttonReset->setEnabled(true);
}

// -----------------------------------------------------------------------------
void CardEditor::reset() {
	
	// Uncheck all groups
	ui.groupDamage->setChecked(false);
	ui.groupFlags->setChecked(false);
	ui.groupResourceMatrix->setChecked(false);
	ui.groupModiferMatrix->setChecked(false);
	ui.groupScripts->setChecked(false);
	
	// Tables
	// Resource Matrix
	std::string value[] = { "Bricks", "Gems", "Beasts","Tower","Wall" };
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 5; j++) {
			QTableWidgetItem* item = new QTableWidgetItem();
			item->setData(Qt::DisplayRole, 0);
			ui.tableResources->setItem(i,j, item);
		}
	}

	// Modifer Matrix
	std::string mods[] = { "BrickMod", "MagicMod", "BeastMod" };
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 3; j++) {
			QTableWidgetItem* item = new QTableWidgetItem();
			item->setData(Qt::DisplayRole, 0);
			ui.tableModifiers->setItem(i,j, item);
		}
	}

	ui.tableModifiers->reset();
	ui.tableResources->reset();

	// Flags
	ui.checkAddTurn->setChecked(false);
	ui.checkDiscard->setChecked(false);
	ui.checkNotDiscardable->setChecked(false);

	// Basic Card Properties
	ui.dropDownCardType->setCurrentIndex(0);
	ui.spinRequirements->setSuffix(" Bricks");
	ui.editCardName->setText("");
	ui.spinRequirements->setValue(0);

	// Damage
	ui.spinDamageSelf->setValue(0);
	ui.spinDamageOpponent->setValue(0);

	// Text 
	ui.textCardCaption->setPlainText("");

	// Image, Script
	ui.imageName->setText("<none>");
	ui.scriptFile->setText("<none>");
	ui.imagePreview->setPixmap(_project && _project->isLegacyDeck() 
		? QPixmap(":/DeckEditor/Resources/Icons/missing-image.png")
		: QPixmap(":/DeckEditor/Resources/Icons/frame-atlas.png"));
	
	// Buttons
	ui.buttonApply->setEnabled(false);
	ui.buttonReset->setEnabled(false);
	hasChanged = false;
}
// -----------------------------------------------------------------------------
void CardEditor::selectImage() {
	QString fileName;
	bool _continue = true;
	fileName = QFileDialog::getOpenFileName(this,
		tr("Open Deck File"), 
		lastDirectory.isEmpty() 
		? QDesktopServices::storageLocation(QDesktopServices::PicturesLocation)
		: lastDirectory, 
		tr("Images (*.png *.jpg *.jpeg)"));

	if(!fileName.isEmpty()) {
		this->lastDirectory = QFileInfo(fileName).canonicalPath();

		std::string file(Util::toStdString(QFileInfo(fileName).fileName()));
		std::string newfile(_project->getWorkingPath()+"/images/"+file);
	
		if(boost::filesystem::exists(newfile)) {
			// A File Size based check may not be the best idea...
			if((boost::filesystem::file_size(Util::toStdString(fileName)) == boost::filesystem::file_size(newfile))) {
				_continue = false;
			} else {
				QMessageBox msgBox;
				msgBox.setText(tr("An Image with the filename \"%1\" already exists in the Deck.\n"
					"You can either replace the existing file or import the image under another name.\n"
					"To use the existing image, press 'Cancel'.").arg(QFileInfo(fileName).fileName()));
				msgBox.setWindowTitle(tr("Image Filename taken"));
				msgBox.setIcon(QMessageBox::Warning);
				QPushButton *repBtn = msgBox.addButton(tr("Replace"), QMessageBox::ActionRole);
				QPushButton *renBtn =  msgBox.addButton(tr("Rename"), QMessageBox::ActionRole);
				QPushButton *abrtBtn = msgBox.addButton(QMessageBox::Cancel);
				msgBox.exec();

				if(msgBox.clickedButton() == repBtn) {		
					boost::filesystem::remove (newfile);
				} else if(msgBox.clickedButton() == renBtn) {
					bool ok;
					boost::filesystem::path propose(boost::filesystem::path(file).filename());
				
					QString text = QInputDialog::getText(this, 
						tr("Import Image"),
						tr("Please enter the internal filename"), QLineEdit::Normal,
						QString("%1_2_%2").arg(propose.stem().c_str(), propose.extension().c_str()), &ok);

					if (ok && !text.isEmpty()) { 
						file = Util::toStdString(text);
						newfile = _project->getWorkingPath()+"/images/"+file;
						ui.imageName->setText(text);
					} else {
						_continue = false;
					}
				} else {
					_continue = false;
				}
			}
		}

		if(_continue) {
			boost::filesystem::copy_file (Util::toStdString(fileName), newfile);
			AtlasGenerator gen(cards);

			gen.addFile(file);

			Rocket::Core::Factory::ClearStyleSheetCache();

			Arcomage::UI::UIManager::getInstance().setActiveUI(
				"Editor/Resources", 
				"Editor3D.uidef",
				true);
			updateCardDisplay(current);
		}
			Arcomage::UI::UIManager::getInstance().setCardProperty(0, "Image", file);
			ui.imageName->setText(QFileInfo(fileName).fileName());
			ui.imageName->setEnabled(true);
			ui.imagePreview->setPixmap(QPixmap(fileName));

			somethingChanged();
		
	}
}

// -----------------------------------------------------------------------------
void CardEditor::resetChanges(){
	hasChanged = false;

	// Simply fetch data gain
	if(current) display(current);
}

// -----------------------------------------------------------------------------
void CardEditor::applyChanges(){
	storeCardChanges();

	ui.buttonApply->setEnabled(false);
	ui.buttonReset->setEnabled(false);
	hasChanged = false;
}
// -----------------------------------------------------------------------------
void CardEditor::changeCardType() {
	int index = ui.dropDownCardType->currentIndex();
	if(index == 0) { // Red
		ui.spinRequirements->setSuffix(" Bricks");
	} else if(index == 1) { // Blue
		ui.spinRequirements->setSuffix(" Gems");
	} else if(index == 2) { // Green
		ui.spinRequirements->setSuffix(" Creatures");
	}

	if(current) {
		Arcomage::UI::UIManager::getInstance().setCardProperty(0,"Type", Arcomage::Utility::toString(index));
	}
}
// -----------------------------------------------------------------------------
void CardEditor::requirementsChanged() {
	somethingChanged();

	Arcomage::UI::UIManager::getInstance().setCardProperty(0,
		"Reqs", Util::toStdString(QString("%1").arg(ui.spinRequirements->value())));
}

// -----------------------------------------------------------------------------
void CardEditor::nameChanged() {
	somethingChanged();

	Arcomage::UI::UIManager::getInstance().setCardProperty(0,"Name", Util::toStdString(ui.editCardName->text()));
}

// -----------------------------------------------------------------------------
void CardEditor::addCardToList(Arcomage::Card* card, int index) {
	QTreeWidgetItem* item = new QTreeWidgetItem(ui.cardList);
	
	item->setData(0, Qt::DisplayRole, index+1);

	int type = card->getValue("Type");
	if(type == 0) {
		item->setIcon(1, QIcon(":/DeckEditor/Resources/Icons/red.png"));
		item->setText(1, "Q");
	} else if(type == 1) {
		item->setIcon(1, QIcon(":/DeckEditor/Resources/Icons/blue.png"));
		item->setText(1, "M");
	} else {
		item->setIcon(1, QIcon(":/DeckEditor/Resources/Icons/green.png"));
		item->setText(1, "B");
	}

	item->setText(2, Util::toQString(card->getName()));
}

// -----------------------------------------------------------------------------
void CardEditor::removeCard() {
	// Only works if an item is selected, of course
	if(ui.cardList->currentItem()) {
		QMessageBox msgBox;
		msgBox.setText(tr("Do you really want to delete the Card \"%1\"?").arg(current->getName().c_str()));
		msgBox.setWindowTitle(tr("Really remove Card?"));
		msgBox.setIcon(QMessageBox::Question);
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::Yes);

		if(msgBox.exec() == QMessageBox::Yes) {		
			ui.cardList->takeTopLevelItem(ui.cardList->indexOfTopLevelItem(ui.cardList->currentItem()));
			current->setFlag(Arcomage::CF_Deleted);

			currentItem = ui.cardList->currentItem();
			if(currentItem) {
				current = cards.at(currentItem->text(0).toInt()-1);
				display(current);
			} else {
				current = new Arcomage::Card(cards.size()+1);
				reset();
			}
		
		}
	}
}

// -----------------------------------------------------------------------------
void CardEditor::addCard() {
	bool ok;
	QString text = QInputDialog::getText(this, tr("Add new Card"),
		tr("Please enter the name of the new Card:"), 
		QLineEdit::Normal, "", &ok);
	if(ok) {
		// cardCount == index + 1
		cardCount++;
		Arcomage::Card* card = new Arcomage::Card(cardCount);
		card->setAttribute("Name", Util::toStdString(text));
		card->setAttribute("Type", 0);
		cards.push_back(card);
		addCardToList(card, cardCount-1);
	}
}
// -----------------------------------------------------------------------------
void CardEditor::display(Arcomage::Card* card) {
	reset();

	// Basic Properties
	ui.editCardName->setText(Util::toQString(card->getName()));
	ui.dropDownCardType->setCurrentIndex(card->getValue("Type"));
	changeCardType();
	ui.spinRequirements->setValue(card->getValue("Requirements"));
	
	// Damage
	ui.spinDamageOpponent->setValue(card->getValue("DamageEnemy"));
	ui.spinDamageSelf->setValue(card->getValue("DamageSelf"));
	ui.groupDamage->setChecked(ui.spinDamageOpponent->value() > 0 || ui.spinDamageSelf->value() > 0);


	// Flags
	ui.checkAddTurn->setChecked(card->hasFlag(Arcomage::CF_ProvidesAdditionalTurn));
	ui.checkDiscard->setChecked(card->hasFlag(Arcomage::CF_DiscardACard));
	ui.checkNotDiscardable->setChecked(card->hasFlag(Arcomage::CF_NotDiscardable));
	ui.groupFlags->setChecked( ui.checkAddTurn->isChecked() ||
				 ui.checkDiscard->isChecked() ||
				 ui.checkNotDiscardable->isChecked() );

	std::string player[] = { "Player", "Enemy" };

	// Resource Matrix
	std::string value[] = { "Bricks", "Gems", "Beasts","Tower","Wall" };
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 5; j++) {
			int val = card->getValue(player[i]+value[j]);
			QTableWidgetItem* item = new QTableWidgetItem();
			item->setData(Qt::DisplayRole, val);
			ui.tableResources->setItem(i,j, item);
			if(val != 0) ui.groupResourceMatrix->setChecked(true);
		}
	}

	// Modifer Matrix
	std::string mods[] = { "BrickMod", "MagicMod", "BeastMod" };
	for(int i = 0; i < 2; i++) {
		for(int j = 0; j < 3; j++) {
			int val = card->getValue(player[i]+mods[j]);			
			QTableWidgetItem* item = new QTableWidgetItem();
			item->setData(Qt::DisplayRole, val);
			ui.tableModifiers->setItem(i,j, item);
			if(val != 0) ui.groupModiferMatrix->setChecked(true);
		}
	}

	// Description
	Rocket::Core::String s(card->getString("Description").c_str());
	s = s.Replace("_n", "\n");
	ui.textCardCaption->setPlainText(s.CString());

	// Script
	ui.groupScripts->setChecked(card->hasFlag(Arcomage::CF_HasScript));
	if(card->hasFlag(Arcomage::CF_HasScript)) {
		ui.scriptFile->setEnabled(true);
		ui.scriptFile->setText(card->getString("ScriptFile").c_str());
	}

	// Image
	if(_project->isLegacyDeck()) {
		QString path = QString("%1/images/%2").arg(_project->getWorkingPath().c_str(), card->getString("Image").c_str());
		
		ui.imagePreview->setPixmap(
				boost::filesystem::exists(Util::toStdString(path)) 
				? QPixmap(path) 
				: QPixmap(":/DeckEditor/Icons/missing-image.png")
			);

	}

	Arcomage::UI::UIManager::getInstance().setCardProperty(0, "Image",  card->getString("Image"));

	ui.imageName->setEnabled(true);
	ui.imageName->setText(Util::toQString(card->getString("Image")));

	
	ui.buttonApply->setEnabled(false);
	ui.buttonReset->setEnabled(false);
	hasChanged = false;
}

// -----------------------------------------------------------------------------
void CardEditor::captionChanged() {
	somethingChanged();

	// We need to replace HTML specific tags, since Rocket is still HTML based.
	Rocket::Core::String text(Util::toStdString(ui.textCardCaption->toPlainText()).c_str());
	text = text.Replace("\n", "_n");
	text = text.Replace("<", "&lt;"); // To enable users to type < and > which
	text = text.Replace(">", "&gt;"); // are commonly used in card descriptions...

	Arcomage::UI::UIManager::getInstance().setCardProperty(0,"Desc", text.CString());
}

// -----------------------------------------------------------------------------
void CardEditor::updateCardDisplay(Arcomage::Card* card) {
	Arcomage::UI::UIManager& uiMngr = Arcomage::UI::UIManager::getInstance();

	int requirements = card->getValue("Requirements");
	int type = card->getValue("Type");
	uiMngr.setCardProperty(0, "Type",  Arcomage::Utility::toString(type));
	uiMngr.setCardProperty(0, "Name",  card->getName());
	uiMngr.setCardProperty(0, "Image", card->getString("Image"));
	uiMngr.setCardProperty(0, "Desc",  card->getString("Description"));
	uiMngr.setCardProperty(0, "Reqs",  Arcomage::Utility::toString(requirements));
	
}

// -----------------------------------------------------------------------------
void CardEditor::treeItemClicked(const QModelIndex& index) {
	bool _continue = true;
	if(ui.cardList->currentItem()->text(0).toInt() != current->getValue("ID")) { 
		if(hasChanged) {
			QMessageBox msgBox;
			msgBox.setText(tr("Do you want to update the card with the changes you made?"));
			msgBox.setWindowTitle(tr("Save changes?"));
			msgBox.setIcon(QMessageBox::Question);
			msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
			msgBox.setDefaultButton(QMessageBox::Yes);

			QTreeWidgetItem* item = ui.cardList->currentItem();
			int val = msgBox.exec() ;
			if(val == QMessageBox::Yes) {
				if((_continue = storeCardChanges())) {
					hasChanged = false;
				} 
			} else if (val == QMessageBox::Cancel) {
				_continue = false;
				
				// Switch selection back to previous item on Cancel
				ui.cardList->setItemSelected(ui.cardList->currentItem(), false);
				ui.cardList->setItemSelected(currentItem, true);
			} else {
				hasChanged = false;
			}
		} 

		if(_continue) {
			current = cards.at(ui.cardList->currentItem()->text(0).toInt()-1);
			updateCardDisplay(current);
			display(current);
			currentItem = ui.cardList->currentItem();
		}
	}
}

// -----------------------------------------------------------------------------
void CardEditor::validateValues() {
	std::string player[] = { "Player", "Enemy" };

	// Resource Matrix
	std::string value[] = { "Bricks", "Gems", "Beasts","Tower","Wall" };
	QTableWidgetItem* temp;


	if(ui.groupResourceMatrix->isChecked()) {
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 5; j++) {
				temp = ui.tableResources->item(i, j);
				int data = temp->data(Qt::DisplayRole).toInt();
				if(data != 0) {
					if(data > 30)
						data = 30;
					if(data < -30)
						data = -30;

					temp->setData(Qt::DisplayRole, data);
				}
			}
		}
	}

	if(ui.groupModiferMatrix->isChecked()) {
		// Modifer Matrix
		std::string mods[] = { "BrickMod", "MagicMod", "BeastMod" };
		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 3; j++) {
				temp = ui.tableModifiers->item(i, j);
				int data = temp->data(Qt::DisplayRole).toInt();

				// Silently Apply Constraint that data has to bewithin [-30;30]
				if(data != 0) {
					if(data > 30)
						data = 30;
					if(data < -30)
						data = -30;
				
					temp->setData(Qt::DisplayRole, data);
				}
			}
		}
	}
}

// -----------------------------------------------------------------------------
bool CardEditor::storeCardChanges() {
	if(ui.imageName->text() != "<none>") {
		if(current->getName() != Util::toStdString(ui.editCardName->text())) {
			currentItem->setText(2, ui.editCardName->text());
		}
		
		current->setAttribute("Name", Util::toStdString(ui.editCardName->text()));
		
		current->setAttribute("Type", ui.dropDownCardType->currentIndex());
		current->setAttribute("Image", Util::toStdString(ui.imageName->text()));
		current->setAttribute("Requirements", ui.spinRequirements->value());

	
		// Flags
		ui.checkAddTurn->isChecked() ? current->setFlag(Arcomage::CF_ProvidesAdditionalTurn) 
									 : current->unsetFlag(Arcomage::CF_ProvidesAdditionalTurn);
		ui.checkDiscard->isChecked() ? current->setFlag(Arcomage::CF_DiscardACard) 
									 : current->unsetFlag(Arcomage::CF_DiscardACard);
		ui.checkNotDiscardable->isChecked() ? current->setFlag(Arcomage::CF_NotDiscardable) 
											: current->unsetFlag(Arcomage::CF_NotDiscardable);
		// Damage

		current->setAttribute("DamageSelf", ui.spinDamageSelf->value());
		current->setAttribute("DamageEnemy", ui.spinDamageOpponent->value());
		
		std::string player[] = { "Player", "Enemy" };

		// Resource Matrix
		std::string value[] = { "Bricks", "Gems", "Beasts","Tower","Wall" };


		if(ui.groupResourceMatrix->isChecked()) {
			for(int i = 0; i < 2; i++) {
				for(int j = 0; j < 5; j++) {
					current->setAttribute(player[i]+value[j], ui.tableResources->item(i, j)->data(Qt::DisplayRole).toInt());
				}
			}
		}
		// Modifier Matrix
		std::string mods[] = { "BrickMod", "MagicMod", "BeastMod" };

		if(ui.groupModiferMatrix->isChecked()) {
			for(int i = 0; i < 2; i++) {
				for(int j = 0; j < 3; j++) {
					current->setAttribute(player[i]+mods[j], ui.tableModifiers->item(i, j)->data(Qt::DisplayRole).toInt());
				}
			}
		}
		
		// Description
		current->setAttribute("Description", Util::toStdString(ui.textCardCaption->toPlainText()));

		// Script
		if(ui.scriptFile->text() != "<none>")
			current->setAttribute("ScriptFile", Util::toStdString(ui.scriptFile->text()));
	
		return true;
	} else {
		QMessageBox::critical(this, tr("ERROR"),
			tr("No Image File was selected.\n"
			"A card requires an image, please select one."), QMessageBox::Ok);
			return false;
	}
}

// -----------------------------------------------------------------------------
void CardEditor::releaseEditorResources() {
	if(!rsError) {
		OgreSystem::getInstance().setUIRenderingEnabled(false);
	//	Ogre::Root::getSingletonPtr()->getSceneManager("root")->destroyAllCameras();
		//Arcomage::UI::UIManager::getInstance().shutdown();
		
		OgreSystem::getInstance().unregisterWidget(widget);
		widget->deleteLater();
	} 

	_project->cleanUp();
//	EditorSystem::getInstance().increaseInstanceCount();
}
// -----------------------------------------------------------------------------
void CardEditor::loadEditorResources() {
	if(!rsError) {

	}
}

