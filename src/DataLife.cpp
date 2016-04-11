#include "DataLife.h"



DataLife::DataLife()
{
	this->settings = new ofxXmlSettings();
	this->settings->loadFile("config.xml");

	this->speedLifeGame = this->settings->getValue("settings:speedLifeGame", 83);
	this->limitTrees = this->settings->getValue("settings:limitTrees", 1024);
	this->limitHerbi = this->settings->getValue("settings:limitHerbi", 512);
	this->limitCarni = this->settings->getValue("settings:limitCarni", 512);
	this->limitInvade = this->settings->getValue("settings:limitInvade", 1200);
	this->portServer = 11900;// this->settings->getValue("settings:portServer", 11900);

	this->soundMainLevel = this->settings->getValue("settings:soundMainLevel", 1.0f);

	this->showCircleMap = this->settings->getValue("settings:showCircleMap", 0) == 1;
	this->launchInvade = this->settings->getValue("settings:launchInvade", 0) == 1;
}


DataLife::~DataLife()
{
}
