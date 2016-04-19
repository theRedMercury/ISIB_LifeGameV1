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

	this->limitTrees = this->settings->getValue("params:trees:minLim", 1024);
	this->minTrees = this->settings->getValue("params:trees:maxLim", 15);

	this->limitHerbi = this->settings->getValue("params:herbi:maxLimi", 512);
	this->ageDeadHerbi = this->settings->getValue("params:herbi:ageDead", 100);
	this->ageHerbiRand = this->settings->getValue("params:herbi:ageRand", 20);
	this->minHerbi = this->settings->getValue("params:herbi:minLim", 15);

	this->limitCarni = this->settings->getValue("params:carni:maxLim", 512);
	this->ageDeadCarni = this->settings->getValue("params:carni:ageDead", 50);
	this->ageCarniRand = this->settings->getValue("params:carni:ageRand", 30);
	this->minCarni = this->settings->getValue("params:carni:minLim", 5);

	this->ageDeadInvad = this->settings->getValue("params:invade:ageDead", 80);
	this->ageInvadRand = this->settings->getValue("params:invade:ageRand", 25);
	this->limitInvade = this->settings->getValue("params:invade:maxLim", 1200);


	this->settings->clear();
	delete this->settings;
}


DataLife::~DataLife()
{
}
