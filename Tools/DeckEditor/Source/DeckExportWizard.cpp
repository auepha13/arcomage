#include "DeckExportWizard.h"
#include "EditorProject.h"
#include "DeckExporter.h"

#include "ToolkitUtil.h"
#include <boost/filesystem.hpp>

// -----------------------------------------------------------------------------
DeckExportWizard::DeckExportWizard(const QString& previousFilename, EditorProject* project, QWidget *parent /* = 0 */) 
	: QWizard(parent), 
	fileName(previousFilename),
	project(project) {
		ui.setupUi(this);
		setPixmap(QWizard::LogoPixmap, QPixmap(":/DeckEditor/Resources/Icons/folder-export.png"));
		connect(ui.buttonSelectFile, SIGNAL(clicked()), this, SLOT(selectFileName()));
	//	ui.file->setText(fileName);
		connect(this, SIGNAL(currentIdChanged(int)), this, SLOT(exportProject()));
}

// ----------------------------------------------------------------------------- 
void DeckExportWizard::selectFileName() {
	fileName = QFileDialog::getSaveFileName(this, tr("Export File as"),
		QFileInfo(ui.file->text()).canonicalPath(),
		tr("Deck Files (*.deck)"));
	ui.file->setText(fileName);
}

// ----------------------------------------------------------------------------- 
void DeckExportWizard::log(const QString& msg) {
	ui.exporterOutput->appendPlainText(msg);
	ui.exporterOutput->repaint();
}

// -----------------------------------------------------------------------------
void DeckExportWizard::exportProject() {

	if(currentId() == 1) {

		bool _continue = true;

		QString file = ui.file->text();
		std::string _file = Util::toStdString(file);
		boost::filesystem::path p(project->getDeckMetaData()->getMetaData("Filename"));

		if(p.normalize().string() == boost::filesystem::path(_file).normalize().string() 
			&& !ui.noPrompt->isChecked()) {
			QMessageBox msgBox;
			msgBox.setText(tr("You are trying to export the Deck with the filename \"%1\" to same file you have imported.\n"
				"You can either overwrite the existing file or save the deck under another name.\n"
				"If you choose to overwrite the file, you will lose all data prior to your modification.").arg(QFileInfo(file).fileName()));
			msgBox.setWindowTitle(tr("Deck already exists"));
			msgBox.setIcon(QMessageBox::Warning);
			QPushButton *repBtn = msgBox.addButton(tr("Overwrite"), QMessageBox::ActionRole);
			QPushButton *renBtn =  msgBox.addButton(tr("Choose new Filename"), QMessageBox::ActionRole);
			QPushButton *abrtBtn = msgBox.addButton(QMessageBox::Abort);
			msgBox.exec();

			if(msgBox.clickedButton() == repBtn) {	
				try {
					boost::filesystem::remove (_file);
				} catch(boost::exception& e) {
					_continue = false;
				}
				//
			} else if(msgBox.clickedButton() == renBtn) {
				QString text = QFileDialog::getSaveFileName(this, tr("Export File as"),
					QFileInfo(file).canonicalPath(),
					tr("Deck Files (*.deck)"));

				if (!text.isEmpty()) { 
					_file = Util::toStdString(text);
					ui.file->setText(text);
				} else {
					_continue = false;
				}

			} else {
				_continue = false;
			}			
		}

		if(_continue) { 
			DeckExporter exp = DeckExporter(project, this, this);
			exp.show();
			exp.exportProject(DECK_API_10);
			exp.close();

		} else  {
			log(tr("[!] ERROR: Operation aborted: Deck already exists or File in use!\n"
				"No action was taken. Please re-run the Wizard."));
		}
	}
}