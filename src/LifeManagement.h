#pragma once

#include <chrono>
#include <thread>
#include <time.h>

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
	~LifeManagement();

private:

	void updateLifeTime();
	void runUpdateVege();
	void runUpdateHerbi();
	void runUpdateCarni();
	void runUpdatePackPos();


	//----------------------------------------------
	stringstream dataToScreenLeft;
	uint64_t counterLife;


	thread lifeTimeThread;
	thread threadUpdatePack;
	thread threadUpdateHerbi;
	thread threadUpdateCarni;

	ToolsLifeGame * tools;
	SocketServer * mainServer = nullptr;
	SoundLife * soundLife = nullptr;
	DataLife * dataLife = nullptr;
	Map * mapLife = nullptr;


	ofImage * herbivorImage = nullptr;
	ofImage * carnivorImage = nullptr;
	ofImage * invasiveImage = nullptr;
};


