#pragma once

#include <chrono>
#include <thread>
#include <time.h>
#include <iostream>
#include <fstream>

#include "Audio/SoundLife.h"

#include "ToolsLifeGame.h"
#include "SocketServer.h"
#include "DataLife.h"
#include "Map.h"


class LifeManagement
{
public:
	LifeManagement();
	void init();
	void update();
	void draw();
	void setInvasiv();
	~LifeManagement();

private:

	void updateLifeTime();
	void runUpdateAnimation();
	void runUpdateVege();
	void runUpdateHerbi();
	void runUpdateCarni();
	void runUpdateInvade();
	void runUpdatePackPos();

	//----------------------------------------------
	ofstream  fileSave;
	stringstream dataToScreenLeft;
	uint64_t counterLife;
	bool runAllThread;

	thread lifeTimeThread;
	thread threadUpdateAnimation;
	thread threadUpdatePack;
	thread threadUpdateHerbi;
	thread threadUpdateCarni;
	thread threadUpdateInvade;

	SocketServer * mainServer = nullptr;
	SoundLife * soundLife = nullptr;
	DataLife * dataLife = nullptr;
	Map * mapLife = nullptr;

	ofImage * herbivorImage = nullptr;
	ofImage * carnivorImage = nullptr;
	ofImage * invasiveImage = nullptr;
};


