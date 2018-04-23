#include "ProjectWizard.h"
#include "DeckMetaData.h"
#include "EditorProject.h"
#include "ToolkitUtil.h"

#include <QFileDialog>

ProjectWizard::ProjectWizard(EditorProject* project, QWidget *parent /* = 0 */) 
 : QWizard(parent) {
	 ui.setupUi(this);
	 setPixmap(QWizard::LogoPixmap, QPixmap(":/DeckEditor/Resources/Icons/icon.png"));

	 Arcomage::DeckMetaData* data = project->getDeckMetaData();

	ui.deckName->setText(Util::toQString(data->getMetaData("Name")));
	ui.authorName->setText(Util::toQString(data->getMetaData("Author")));
	ui.deckVersion->setText(Util::toQString(data->getMetaData("Version")));
	ui.deckDescription->setPlainText(Util::toQString(data->getMetaData("Description")));
	ui.projectName->setText(Util::toQString(data->getMetaData("Name")));

	connect(ui.buttonBrowseLocation,  SIGNAL(clicked()), this, SLOT(browseLocation()));

}

void ProjectWizard::browseLocation() {
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
		QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation),
		QFileDialog::ShowDirsOnly
		| QFileDialog::DontResolveSymlinks);
	
	ui.deckLocation->setText(dir);
}