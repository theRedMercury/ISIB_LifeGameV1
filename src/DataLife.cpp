#include "DataLife.h"



DataLife::DataLife()
{
	this->settings = new ofxXmlSettings();
	this->settings->loadFile("config.xml");
	
	if (this->settings->getValue("settings:fullScreen", 0) == 1) {
		ofSetFullscreen(true);
		ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
	}

	this->speedLifeGame = this->settings->getValue("settings:speedLifeGame", 83);
	this->portServer = this->settings->getValue("settings:portServer", 11900);
	this->showCircleMap = this->settings->getValue("settings:showCircleMap", 0) == 1;
	this->launchInvade = this->settings->getValue("settings:launchInvade", 0) == 1;
	this->saveData = this->settings->getValue("settings:saveData", 0) == 1;

	this->soundMainLevel = this->settings->getValue("settings:sound:mainLevel", 1.0f);
	this->soundAmbience = this->settings->getValue("settings:sound:ambience", 1.0f);
	this->soundMelody = this->settings->getValue("settings:sound:melody", 1.0f);
	this->soundInvade = this->settings->getValue("settings:sound:invade", 1.0f);
	this->soundEating = this->settings->getValue("settings:sound:eating", 1.0f);
	this->soundSpeed = this->settings->getValue("settings:sound:speePlay", 1.0f);

	this->limMaxTrees = this->settings->getValue("params:trees:lim:max", 1024);
	this->addTrees = this->settings->getValue("params:trees:addTree", 10);
	this->limMinTrees = this->settings->getValue("params:trees:lim:min", 15);


	this->limMaxHerbi = this->settings->getValue("params:herbi:lim:max", 512);
	this->ageDeadHerbi = this->settings->getValue("params:herbi:age:dead", 100);
	this->ageRandHerbi = this->settings->getValue("params:herbi:age:rand", 20);
	this->limMinHerbi = this->settings->getValue("params:herbi:lim:min", 15);
	this->gestationYearHerbi = this->settings->getValue("params:herbi:reproduction:gestationyear", 3);
	this->weaningYearHerbi = this->settings->getValue("params:herbi:reproduction:weaningyear", 7);
	this->visionStartHerbi = (float)this->settings->getValue("params:herbi:vision:start", 65.0f);
	this->visionMaxHerbi = (float)this->settings->getValue("params:herbi:vision:max", 65.0f);
	this->visionAngleHerbi = (float)this->settings->getValue("params:herbi:vision:angle", 65.0f);
	this->visionShowHerbi = this->settings->getValue("params:herbi:vision:show",0) == 1;

	this->limMaxCarni = this->settings->getValue("params:carni:lim:max", 512);
	this->ageDeadCarni = this->settings->getValue("params:carni:age:dead", 50);
	this->ageRandCarni = this->settings->getValue("params:carni:age:rand", 30);
	this->limMinCarni = this->settings->getValue("params:carni:lim:min", 5);
	this->gestationYearCarni = this->settings->getValue("params:carni:reproduction:gestationyear", 5);
	this->weaningYearCarni = this->settings->getValue("params:carni:reproduction:weaningyear", 10);
	this->visionStartCarni = (float)this->settings->getValue("params:carni:vision:start", 65.0f);
	this->visionMaxCarni = (float)this->settings->getValue("params:carni:vision:max", 65.0f);
	this->visionAngleCarni = (float)this->settings->getValue("params:carni:vision:angle", 65.0f);
	this->visionShowCarni = this->settings->getValue("params:carni:vision:show", 0) == 1;


	this->ageDeadInvad = this->settings->getValue("params:invade:age:dead", 80);
	this->ageRandInvad = this->settings->getValue("params:invade:age:rand", 25);
	this->limMaxInvad = this->settings->getValue("params:invade:lim:max", 1200);


	this->settings->clear();
	delete this->settings;
}


DataLife::~DataLife()
{
}
