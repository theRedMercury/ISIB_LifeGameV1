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

	//Params---------------------------------------------------
	unsigned int speedLifeGame = 83;	//msSleep
	unsigned int portServer = 11900;
	bool showCircleMap = false;
	bool launchInvade = true;
	bool saveData = false;

	//Sound Params =========================
	float soundMainLevel = 0.0f;
	float soundAmbience = 0.0f;
	float soundMelody = 0.0f;
	float soundInvade = 0.0f;
	float soundEating = 0.0f;
	float soundSpeed = 0.0f;

	
	//Trees Params =========================
	unsigned int limMaxTrees = 1024;
	unsigned int addTrees = 10;
	unsigned int limMinTrees = 15;

	//Herbi Params =========================
	unsigned int limMaxHerbi = 512;
	unsigned int limMinHerbi = 15;
	unsigned int ageDeadHerbi = 100;
	unsigned int ageRandHerbi = 50;
	unsigned int gestationYearHerbi = 5;
	unsigned int weaningYearHerbi = 7;
	float visionStartHerbi = 0.0f;
	float visionMaxHerbi = 0.0f;
	float visionAngleHerbi = 0.0f;
	bool  visionShowHerbi = false;

	//Carni Params =========================
	unsigned int limMaxCarni = 512;
	unsigned int limMinCarni = 5;
	unsigned int ageDeadCarni = 100;
	unsigned int ageRandCarni = 50;
	unsigned int gestationYearCarni = 5;
	unsigned int weaningYearCarni = 7;
	float visionStartCarni = 0.0f;
	float visionMaxCarni = 0.0f;
	float visionAngleCarni = 0.0f;
	bool  visionShowCarni = false;

	//Invad Params =========================
	unsigned int limMaxInvad = 1200;
	unsigned int ageDeadInvad = 100;
	unsigned int ageRandInvad = 50;
	

private :
	ofxXmlSettings * settings;
};


