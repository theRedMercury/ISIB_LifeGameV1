#pragma once
#include "ofMain.h"

#include "ofx/ofxXmlSettings/src/ofxXmlSettings.h"

#include "Species/Carnivorous.h"
#include "Species/Herbivorous.h"
#include "Species/Invasive.h"
#include "Species/Vegetable.h"

class Herbivorous;
class Carnivorous;
class Invasive;

class DataLife
{
public:
	DataLife();
	~DataLife();

	mutex lockListTrees;
	mutex lockListHerbi;
	mutex lockListCarni;
	mutex lockListInva;

	list<Invasive*> listInva;
	list<Vegetable*> listTrees;
	list<Herbivorous*> listHerbi;
	list<Carnivorous*> listCarni;

	unsigned int speedLifeGame = 83;	//msSleep
	unsigned int limitTrees = 1024;
	unsigned int limitHerbi = 512;
	unsigned int limitCarni = 512;
	unsigned int limitInvade = 1200;

	unsigned int minTrees = 15;
	unsigned int minHerbi = 15;
	unsigned int minCarni = 5;

	unsigned int ageDeadHerbi = 100;
	unsigned int ageDeadCarni = 100;
	unsigned int ageDeadInvad = 100;


	unsigned int portServer = 11900;

	float soundMainLevel = 0.0f;

	bool showCircleMap = false;
	bool launchInvade = true;


private :
	ofxXmlSettings * settings;
};


