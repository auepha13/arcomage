#include "DeckExporter.h"
#include "DeckExportWizard.h"
#include "EditorProject.h"
#include "ToolkitUtil.h"
#include "PackUtil.h"

#include <boost/filesystem.hpp>

#include <Card.h>
#include <Utility.h>

#include "ArcomageForward.h"
class ProjectExporter {
private:
	EditorProject* project;
	std::string destination;
		boost::filesystem::path exportDir;

public:

	// -------------------------------------------------------------------------
	ProjectExporter(EditorProject* project, const std::string& to) 
		: project(project), destination(to), exportDir("Editor/Cache/_@export/") {
			exportDir.normalize();

			if(boost::filesystem::exists(exportDir))
				boost::filesystem::remove_all(exportDir);

			boost::filesystem::create_directory(exportDir);

			// Unpack the Skeleton file
			PackUtil::unpack("Editor/Skel/0.3.2.0.skel", exportDir.string());
	}

	// -------------------------------------------------------------------------
	void writeMetaData() {
		boost::filesystem::path p(exportDir/"meta.xml");
		p.normalize();
		std::ofstream out(p.string());
		Arcomage::DeckMetaData* data = project->getDeckMetaData();

		out << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << std::endl << std::endl
			<< "<Deck VersionAPI=\"1.0\" GeneratedBy=\"Arcomage Tribute Deck Editor\" Template=\"Default\">" << std::endl
			<< "\t<Name>" << data->getMetaData("Name") << "</Name>" << std::endl
			<< "\t<Description>" << data->getMetaData("Description") << "</Description>" << std::endl
			<< "\t<Author>" << data->getMetaData("Author") << "</Author>"  << std::endl
			<< "\t<Version>" << data->getMetaData("Version") << "</Version>" << std::endl
			<< "\t<Date>" << "--" << "</Date>" << std::endl
			<< "</Deck>";

		out.close();
	}
	// -------------------------------------------------------------------------
	void writeDeckData() {
		boost::filesystem::path p(exportDir/"data"/"deck.xml");
		p.normalize();
		std::ofstream out(p.string());

		out << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << std::endl << std::endl
			<< "<Deck>" << std::endl;
		int i = 1;
		foreach(Arcomage::Card* card, project->getCards()) {
			if(!card->hasFlag(Arcomage::CF_Deleted)) {
				out << "\t<Card id=\"" << i << "\">" << std::endl
					<< "\t\t<Name>"<< card->getName() << "</Name>" << std::endl
					<< "\t\t<Type value=\"" << card->getValue("Type") << "\" />" << std::endl
					<< "\t\t<Picture value=\"" << card->getString("Image") << "\" />" << std::endl
					<< "\t\t<Requirements value=\"" << card->getValue("Requirements") << "\" />" << std::endl; 

				if(card->hasFlag(Arcomage::CF_ProvidesAdditionalTurn))
					out << "\t\t<AdditionalTurn value=\"1\" />" << std::endl; 

				if(card->hasFlag(Arcomage::CF_DiscardACard))
					out << "\t\t<DiscardCard value=\"1\" />" << std::endl; 

				if(card->hasFlag(Arcomage::CF_HasScript))
					out << "\t\t<Script value=\""<< card->getString("ScriptFile") << "\" />" << std::endl; 

				// Damage
					out << "\t\t<Damage enemy=\""<< card->getValue("DamageEnemy") 
						<< "\" self=\"" << card->getValue("DamageSelf")  <<"\" />" << std::endl; 

				// Player Mod Changes
					out << "\t\t<PlayerMod beasts=\""<< card->getValue("PlayerBeastMod") 
						<< "\" bricks=\"" << card->getValue("PlayerBrickMod") 
						<< "\" gems=\"" << card->getValue("PlayerMagicMod")  <<"\" />" << std::endl; 
				// Enemy Mod Changes
					out << "\t\t<EnemyMod beasts=\""<< card->getValue("EnemyBeastMod") 
						<< "\" bricks=\"" << card->getValue("EnemyBrickMod") 
						<< "\" gems=\"" << card->getValue("EnemyMagicMod")  <<"\" />" << std::endl; 

				// Player Resource Changes
					out << "\t\t<PlayerChanges beasts=\""<< card->getValue("PlayerBeasts") 
						<< "\" bricks=\"" << card->getValue("PlayerBricks") 
						<< "\" gems=\"" << card->getValue("PlayerGems") 
						<< "\" tower=\"" << card->getValue("PlayerTower") 
						<< "\" wall=\"" << card->getValue("PlayerWall")  <<"\" />" << std::endl; 

				// Enemy Resource Changes
					out << "\t\t<EnemyChanges beasts=\""<< card->getValue("EnemyBeasts") 
						<< "\" bricks=\"" << card->getValue("EnemyBricks") 
						<< "\" gems=\"" << card->getValue("EnemyGems") 
						<< "\" tower=\"" << card->getValue("EnemyTower") 
						<< "\" wall=\"" << card->getValue("EnemyWall")  <<"\" />" << std::endl; 
				out << "\t\t<Description>";

				boost::regex _expr("_n"); 
				std::string _fmt("\\n"); 
				std::string _str = boost::regex_replace(card->getString("Description"), _expr, _fmt);
				boost::regex expr("\\n"); 
				std::string fmt("_n"); 
				std::string s = boost::regex_replace(_str, expr, fmt);

				out << s;
	
				out << "</Description>"<< std::endl;
				out	<< "\t</Card>" << std::endl;
				i++;
			}
		}
		
		out	<< "</Deck>" << std::endl;
		out.close();
	}

	// -------------------------------------------------------------------------
	void packImages() {
		Arcomage::CardVector& v = project->getCards();
		foreach(Arcomage::Card* card, project->getCards()) {
			if(!card->hasFlag(Arcomage::CF_Deleted)) {
				boost::filesystem::path image(project->getWorkingPath());
				image.normalize();
				image = image/"images"/card->getString("Image");

				if(boost::filesystem::exists(image)) {
					if(!boost::filesystem::exists(exportDir/"images"/card->getString("Image")))
						boost::filesystem::copy_file(image.string(), exportDir/"images"/card->getString("Image"));
				}			
			}
		}
	}


	// -------------------------------------------------------------------------
	void packScripts() {
		Arcomage::CardVector& v = project->getCards();
		for(Arcomage::CardVector::const_iterator it = v.begin(); it != v.end(); ++it) {
			boost::filesystem::path script(project->getWorkingPath());
			script.normalize();
			script = script/"scripts"/(*it)->getString("ScriptFile");

			if(boost::filesystem::exists(script)) {
				if(!boost::filesystem::exists(exportDir/"scripts"/(*it)->getString("ScriptFile")))
					boost::filesystem::copy_file(script.string(), exportDir/"scripts"/(*it)->getString("ScriptFile"));
			}			
		}
	}

	// -------------------------------------------------------------------------
	void pack() {
		PackUtil::packDir(exportDir.string(), destination);
	}

	// -------------------------------------------------------------------------
	void cleanup() {
		if(boost::filesystem::exists(exportDir))
			boost::filesystem::remove_all(exportDir);
	}

};

// -----------------------------------------------------------------------------
DeckExporter::DeckExporter(EditorProject* project, DeckExportWizard* wizard /* = 0 */, QWidget *parent)
	: project(project),
      wizard(wizard),
	QDialog( parent, Qt::Tool |  Qt::CustomizeWindowHint | Qt::WindowTitleHint){
	setup();
	wizard->log("*---- Arcomage Deck Exporter initialized...");

}

// -----------------------------------------------------------------------------
void DeckExporter::setup() {
	QVBoxLayout* layout = new QVBoxLayout(this);

	progress = new QProgressBar();
	text = new QLabel(tr("Opening..."));
	layout->addWidget(progress);
	layout->addWidget(text);

	setWindowModality(Qt::ApplicationModal);
	adjustSize();

	progress->setMaximum(100);
	progress->setMinimum(0);
	progress->setValue(0);
}


// -----------------------------------------------------------------------------
void DeckExporter::exportProject(DECK_APIVERSION api) {
	QString version(toAPIString(api));
	/*
	ExportImpl* exporter;
	if(api == DECK_API_10)
		exporter = new LegacyExporter(project);
	else if(api == DECK_API_11)
		exporter = new Exporter(project);
	*/
	
	wizard->log("-- Using Skeleton File: 0.3.2.0.skel");
		wizard->log("--- Preparing Skeleton File...");
	ProjectExporter exporter(project, wizard->getFile());
	wizard->log("--- Ok.");

	wizard->log("-- Preparing Metadata...");
	wizard->log("--- Requested API Version: " + version);
	//parent->log("--- Writing Meta Information for Deck: \n--- '" + QFile(parent->getFile()).fileName() + "'");
	text->setText("Metadata...");
	exporter.writeMetaData();
	wizard->log("--- Done");
	progress->setValue(10);

	text->setText("Images...");
	wizard->log("-- Packing Image Files..");
	exporter.packImages();
	wizard->log("--- Done");
		progress->setValue(30);

	text->setText("Scripts...");
	wizard->log("-- Packing Script Files..");
	exporter.packScripts();
	wizard->log("--- Done");
		progress->setValue(40);

	text->setText("Cards...");
	wizard->log("-- Exporting Deck Data..");
	exporter.writeDeckData();
	wizard->log("--- Ok..");
		progress->setValue(70);

	text->setText("Packing...");
	wizard->log("-- Packing Deck..");
	exporter.pack();

	boost::filesystem::path p(wizard->getFile());
	if(boost::filesystem::exists(p)) {
		std::stringstream inf;
		inf << "-- Packing done: " + p.filename();
		inf << " (Size: " << boost::filesystem::file_size(p) << " Bytes)";
		wizard->log(Util::toQString(inf.str()));
	}

	progress->setValue(99);

	// Cleanup
	exporter.cleanup();
	progress->setValue(100);

	wizard->log(QString("-- Successfully exported Deck to ").append(p.string().c_str()));
}

// -----------------------------------------------------------------------------
QString DeckExporter::toAPIString(DECK_APIVERSION api) {
	if(api == DECK_API_10) return "API Version 1.0";
	if(api == DECK_API_11) return "API Version 1.1";
	else return "Unknown API (Exporting will fail for sure...)";
}
