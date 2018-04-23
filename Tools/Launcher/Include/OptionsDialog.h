#ifndef _OptionsDialog_h_
#define _OptionsDialog_h_
#include <QDialog>

#include "ui_OptionsDialog.h"


class ConfigFileCompat;

class OptionsDialog : public QDialog
{
	Q_OBJECT

public:
	OptionsDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
private slots:
	void musicValue(int newVal);
	void effectsValue(int newVal);
	void audioCheckBox();
	void saveSettings();
private:
	Ui::OptionsDialog ui;
	ConfigFileCompat* config;
	void setupConfig();

};
#endif