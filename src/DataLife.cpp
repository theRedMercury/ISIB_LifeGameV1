#include "DataLife.h"



DataLife::DataLife()
{
	this->settings = new ofxXmlSettings();
	this->settings->loadFile("config.xml");

	this->speedLifeGame = this->settings->getValue("settings:speedLifeGame", 83);
	this->portServer = this->settings->getValue("settings:portServer", 11900);
	this->showCircleMap = this->settings->getValue("settings:showCircleMap", 0) == 1;
	this->launchInvade = this->settings->getValue("settings:launchInvade", 0) == 1;

	this->soundMainLevel = this->settings->getValue("settings:sound:mainLevel", 1.0f);

	this->limitTrees = this->settings->getValue("params:maxLimTrees", 1024);
	this->limitHerbi = this->settings->getValue("params:maxLimHerbi", 512);
	this->limitCarni = this->settings->getValue("params:maxLimCarni", 512);
	this->limitInvade = this->settings->getValue("params:maxLimInvad", 1200);

	this->minTrees = this->settings->getValue("params:minLimTrees", 15);
	this->minHerbi = this->settings->getValue("params:minLimHerbi", 15);
	this->minCarni = this->settings->getValue("params:minLimCarni", 5);

	this->ageDeadHerbi = this->settings->getValue("params:ageDeadHerbi", 100);
	this->ageDeadCarni = this->settings->getValue("params:ageDeadCarni", 50);
	this->ageDeadInvad = this->settings->getValue("params:ageDeadInvad", 80);

	this->settings->clear();
	delete this->settings;
}


DataLife::~DataLife()
{
}
