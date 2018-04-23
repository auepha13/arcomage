#include "MetaDataEditor.h"
#include "ToolkitUtil.h"

#include <DeckMetaData.h>

// -----------------------------------------------------------------------------
MetaDataEditor::MetaDataEditor(EditorProject* project, DeckEditor* parentEditor, 
	QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags), 
	EditorWidget(project, parentEditor),
	data(project->getDeckMetaData()) {
		ui.setupUi(this);

		displayMetaData();

		connect(ui.buttonSave, SIGNAL(clicked()), this, SLOT(updateMetaData()));
		connect(ui.buttonReset, SIGNAL(clicked()), this, SLOT(displayMetaData()));

		connect(ui.deckName, SIGNAL(editingFinished()), this, SLOT(changed()));
		connect(ui.deckAuthor, SIGNAL(editingFinished()), this, SLOT(changed()));
		connect(ui.deckVersion, SIGNAL(editingFinished()), this, SLOT(changed()));
		connect(ui.deckDescription, SIGNAL(textChanged()), this, SLOT(changed()));
}

// -----------------------------------------------------------------------------
MetaDataEditor::~MetaDataEditor() {

}

// -----------------------------------------------------------------------------
void MetaDataEditor::displayMetaData() {
	ui.deckName->setText(Util::toQString(data->getMetaData("Name")));
	ui.deckAuthor->setText(Util::toQString(data->getMetaData("Author")));
	ui.deckVersion->setText(Util::toQString(data->getMetaData("Version")));
	ui.deckDescription->setPlainText(Util::toQString(data->getMetaData("Description")));

	ui.date->setText(Util::toQString(data->getMetaData("Date")));
	ui.api->setText(Util::toQString(data->getMetaData("VersionAPI")));

	ui.buttonReset->setEnabled(false);
	ui.buttonSave->setEnabled(false);
}

// -----------------------------------------------------------------------------
void MetaDataEditor::updateMetaData() {
	if(ui.deckName->text().isEmpty() 
		|| ui.deckAuthor->text().isEmpty() 
		|| ui.deckVersion->text().isEmpty()) {
			QMessageBox::warning(qApp->activeWindow(), "Missing Data", tr(
				"Some Data is missing!\n"
				"Every Deck requires a Name, an Author and a Version!\n"
				"These Fields cannot be empty. Please provide the missing information. "),
				QMessageBox::Ok, QMessageBox::Ok);
	} else {
		data->setMetaData("Name", Util::toStdString(ui.deckName->text()));
		data->setMetaData("Author", Util::toStdString(ui.deckAuthor->text()));
		data->setMetaData("Version", Util::toStdString(ui.deckVersion->text()));
		data->setMetaData("Description", Util::toStdString(ui.deckDescription->toPlainText()));

		ui.buttonReset->setEnabled(false);
		ui.buttonSave->setEnabled(false);
	}
}

// -----------------------------------------------------------------------------
void MetaDataEditor::changed() {
	ui.buttonReset->setEnabled(true);
	ui.buttonSave->setEnabled(true);
}

// -----------------------------------------------------------------------------
void MetaDataEditor::setProject(EditorProject* project) {
	this->_project = project;
	data = project->getDeckMetaData();
	displayMetaData();
}
