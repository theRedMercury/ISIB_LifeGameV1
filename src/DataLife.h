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
	unsigned int limitTrees = 1024;
	unsigned int addTrees = 10;
	unsigned int minTrees = 15;

	//Herbi Params =========================
	unsigned int limitHerbi = 512;
	unsigned int minHerbi = 15;
	unsigned int ageDeadHerbi = 100;
	unsigned int ageHerbiRand = 50;

	//Carni Params =========================
	unsigned int limitCarni = 512;
	unsigned int minCarni = 5;
	unsigned int ageDeadCarni = 100;
	unsigned int ageCarniRand = 50;

	//Invad Params =========================
	unsigned int limitInvade = 1200;
	unsigned int ageDeadInvad = 100;
	unsigned int ageInvadRand = 50;
	

private :
	ofxXmlSettings * settings;
};


