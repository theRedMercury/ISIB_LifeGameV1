#pragma once
#include "ofMain.h"

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

	unsigned int speedLifeGame = 32;	//msSleep
	unsigned int limitTrees = 1024;
	unsigned int limitHerbi = 512;
	unsigned int limitCarni = 512;
	unsigned int limitInvade = 512;

	bool showCircleMap = false;
	bool launchInvade = true;
};


