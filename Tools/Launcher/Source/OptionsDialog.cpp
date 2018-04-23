#include "ConfigFileCompat.hpp"
#include "OptionsDialog.h"


// -----------------------------------------------------------------------------
OptionsDialog::OptionsDialog(QWidget *parent /* = 0 */, Qt::WFlags flags /* = 0 */)
		: QDialog(parent, flags), config(new ConfigFileCompat()) {
	setWindowModality(Qt::ApplicationModal );
	ui.setupUi(this);
	setupConfig();

	connect(ui.effectSlider, SIGNAL(valueChanged(int)), this, SLOT(effectsValue(int)));
	connect(ui.musicSlider, SIGNAL(valueChanged(int)), this, SLOT(musicValue(int)));
	connect(ui.checkAudio, SIGNAL(stateChanged(int)), this, SLOT(audioCheckBox()));
	connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.saveButton, SIGNAL(clicked()), this, SLOT(saveSettings()));
}

// -----------------------------------------------------------------------------
void OptionsDialog::setupConfig() {
	if(config && config->load("data/config.xml")) {
		ui.checkAudio->setChecked(config->getValue("audio enabled"));
		audioCheckBox();

		ui.musicSlider->setValue(config->getValue("music volume"));
		musicValue(config->getValue("music volume"));

		ui.effectSlider->setValue(config->getValue("effects volume"));
		effectsValue(config->getValue("effects volume"));

		ui.checkFullscreen->setChecked(config->getValue("screen fullscreen"));
		ui.checkSplash->setChecked(config->getValue("splash enabled"));
	}
}


// -----------------------------------------------------------------------------
void OptionsDialog::musicValue(int newVal) {
	ui.musicPercent->setText(tr("%1%").arg(newVal));
}

// -----------------------------------------------------------------------------
void OptionsDialog::effectsValue(int newVal) {
	ui.effectPercent->setText(tr("%1%").arg(newVal));
}

// -----------------------------------------------------------------------------
void OptionsDialog::audioCheckBox() {
	ui.musicSlider->setEnabled(ui.checkAudio->isChecked());
	ui.effectSlider->setEnabled(ui.checkAudio->isChecked());
}
// -----------------------------------------------------------------------------
void OptionsDialog::saveSettings() {
	if(config) {
		// First off, map all changes to the Config Manager
		config->setValue("audio enabled", ui.checkAudio->isChecked() ? 1 : 0);
		config->setValue("screen fullscreen", ui.checkFullscreen->isChecked() ? 1 : 0);
		config->setValue("splash enabled", ui.checkSplash->isChecked() ? 1 : 0);

		config->setValue("music volume", ui.musicSlider->value());
		config->setValue("effects volume", ui.effectSlider->value());

		// Store stuff
		config->store("data/config.xml");
	}

	// Close window
	close();
}