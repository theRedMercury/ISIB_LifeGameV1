#include "LifeManagement.h"

LifeManagement::LifeManagement()
{
	this->dataLife = new DataLife();
	this->mainServer = new SocketServer(this->dataLife);
	this->soundLife = new SoundLife(0.0);

	this->mapLife = new Map(this->dataLife);


	this->counterLife = 0;
	//testH = new HerbivorousV2();	

	this->vegetalImage = new ofImage();
	if (this->vegetalImage->loadImage("tree.png")) {
		this->vegetalImage->allocate(112, 127, OF_IMAGE_COLOR_ALPHA);
	}
	else {
		delete (this->vegetalImage);
		this->vegetalImage = nullptr;
	}
	

	this->herbivorImage = new ofImage();
	if (this->herbivorImage->loadImage("herbi.png")) {
		this->herbivorImage->allocate(42, 39, OF_IMAGE_COLOR_ALPHA);
	}
	else {
		delete (this->herbivorImage);
		this->herbivorImage = nullptr;
	}
	

	this->carnivorImage = new ofImage("carni.png");
	if (this->carnivorImage->loadImage("carni.png")) {
		this->carnivorImage->allocate(67, 59, OF_IMAGE_COLOR_ALPHA);
	}
	else {
		delete (this->carnivorImage);
		this->carnivorImage = nullptr;
	}

}

void LifeManagement::init()
{
	/*for (int i = 0; i < 15; i++) {
		Vegetable * tree = new Vegetable(this->vegetalImage);
		tree->setPosition(ToolsLifeGame::getRandomPosition(this->posForest, 250));
		tree->setAge(i);
		this->listTrees.push_back(tree);
	}*/

	for (int i = 0; i < 20; i++) {
		Herbivorous * herbi = new Herbivorous(nullptr, this->herbivorImage, this->tools,0);
		//herbi->setPosition(ToolsLifeGame::getRandomPosition(this->tools->listHerPack.at(0),1));
		herbi->setAge(1);
		this->listHerbi.push_back(herbi);
	}
	for (int i = 0; i < 20; i++) {
		Herbivorous * herbi = new Herbivorous(nullptr, this->herbivorImage, this->tools,1);
		//herbi->setPosition(ToolsLifeGame::getRandomPosition(this->tools->listHerPack.at(1), 1));
		herbi->setAge(1);
		this->listHerbi.push_back(herbi);
	}
	

	for (int i = 0; i < 5; i++) {
		Carnivorous * carni = new Carnivorous(nullptr, this->carnivorImage, this->tools,0);
		//carni->setPosition(ToolsLifeGame::getRandomPosition(this->tools->listCarPack.at(0), 1));
		carni->setAge(i);
		this->listCarni.push_back(carni);
	}
	for (int i = 0; i < 5; i++) {
		Carnivorous * carni = new Carnivorous(nullptr, this->carnivorImage, this->tools,1);
		//carni->setPosition(ToolsLifeGame::getRandomPosition(this->tools->listCarPack.at(1), 1));
		carni->setAge(i);
		this->listCarni.push_back(carni);
	}

	this->lifeTimeThread = thread(&LifeManagement::updateLifeTime, this);

	
	this->threadUpdateVege = thread(&LifeManagement::runUpdateVege, this);
	this->threadUpdateHerbi = thread(&LifeManagement::runUpdateHerbi, this);
	this->threadUpdateCarni = thread(&LifeManagement::runUpdateCarni, this);

	this->threadUpdatePack = thread(&LifeManagement::runUpdatePackPos, this);
}


void LifeManagement::runUpdateVege()
{
	int limitGenTree = 0;
	int respanwCooldown = 0;
	while (true)
	{
		this->lockListTrees.lock();
		for (list<Vegetable*>::iterator itTree = this->listTrees.begin(); itTree != this->listTrees.end(); itTree++)
		{
			(*itTree)->aging();
			//Propagation Tree
			
			if ((*itTree)->getAge() > 15 && this->listTrees.size() < this->counterLife) {
				Vegetable * tree = new Vegetable(this->vegetalImage);
				tree->setPosition(this->getRandPositionVeget((*itTree)->getOfVec2f(), 85));
				tree->setAge(1);
				if (tree->getOfVec2f().x != 0 && tree->getOfVec2f().y != 0 && limitGenTree < 3) {
					this->listTrees.push_front(tree);
				}
				limitGenTree += 1;
			}
			limitGenTree = 0;
		}
		
		respanwCooldown += 1;
		//Always Tree
		if (this->listTrees.size() < 10 || respanwCooldown >= 100) {
			respanwCooldown = 0;
			//Forest 
			for (int i = 0; i < 10; i++) {
				Vegetable * tree = new Vegetable(this->vegetalImage);
				tree->setPosition(ToolsLifeGame::getRandomPosition(this->mapLife->getPosForest(), 250));
				tree->setAge(1);
				this->listTrees.push_back(tree);
			}
			//Mountain
			for (int i = 0; i <3; i++) {
				Vegetable * tree = new Vegetable(this->vegetalImage);
				tree->setPosition(ToolsLifeGame::getRandomPosition(this->mapLife->getPosMountain(), 150));
				tree->setAge(1);
				this->listTrees.push_back(tree);
			}
		}
		this->lockListTrees.unlock();
		this->mainServer->sendData("Tree NBR " + to_string(this->listTrees.size()));
		this->mainServer->sendData("Herbi NBR " + to_string(this->listHerbi.size()));
		this->mainServer->sendData("Carni NBR " + to_string(this->listCarni.size()));

		this_thread::sleep_for(chrono::milliseconds(500));
	}
}
void LifeManagement::runUpdateHerbi()
{
	bool nextDestFound = false;
	while (true)
	{
		this->lockListHerbi.lock();
		for (list<Herbivorous*>::iterator itHerbi = this->listHerbi.begin(); itHerbi != this->listHerbi.end(); itHerbi++)
		{
			this->lockListTrees.lock();
			for (list<Vegetable*>::iterator itTree = this->listTrees.begin(); itTree != this->listTrees.end(); itTree++)
			{
				if ((*itHerbi)->getEnergy()<220 &&  ToolsLifeGame::checkCollision((*itHerbi)->getOfVec2f(), (*itTree)->getOfVec2f(), 8)) {
					(*itHerbi)->eating((*itTree)->getAge() / 10);
					(*itTree)->kill();
					
					//this->soundLife->playSoundEatVeg(-(0.5f - ToolsLifeGame::div((*itTree)->getOfVec2f().x , ofGetWidth())));
				}
				else {
					//Intelli Move to Tree 
					if (!nextDestFound &&ToolsLifeGame::checkCollision((*itHerbi)->getOfVec2f(), (*itTree)->getOfVec2f(), 150))
					{
						(*itHerbi)->setNextDesti((*itTree)->getOfVec2f());
						nextDestFound = true;
					}
				}
				nextDestFound = false;
			}
			
			this->lockListTrees.unlock();
			for (list<Herbivorous*>::iterator itHerbiVader = this->listHerbi.begin(); itHerbiVader != this->listHerbi.end(); itHerbiVader++)
			{
				if ((*itHerbi) != (*itHerbiVader) &&
					ToolsLifeGame::checkCollision((*itHerbi)->getOfVec2f(), (*itHerbiVader)->getOfVec2f(), 4) &&
					(*itHerbi)->getSexe() != (*itHerbiVader)->getSexe() && this->listHerbi.size() < this->dataLife->limitCarni)
				{
					(*itHerbiVader)->duplication();
				}
			}
			if ((*itHerbi)->babyReady()) {
				(*itHerbi)->babyBorn();
				Herbivorous * babyHerbi = new Herbivorous((*itHerbi), this->herbivorImage, this->tools);
				babyHerbi->setPosition((*itHerbi)->getOfVec2f());
				babyHerbi->setAge(1);
				//fprintf(stderr, "Born...\n");
				this->listHerbi.push_front(babyHerbi);
			}
			
		}

		if (this->listHerbi.size() < 4) {
			fprintf(stderr, "Add...\n");
			for (int i = 0; i < 15; i++) {
				Herbivorous * babyHerbi = new Herbivorous(nullptr, this->herbivorImage, this->tools,0);
				//babyHerbi->setPosition(ToolsLifeGame::getRandomPosition(this->tools->listHerPack.at(0), 1));
				babyHerbi->setAge(1);;
				this->listHerbi.push_front(babyHerbi);
			}
		}
		this->lockListHerbi.unlock();


		this_thread::sleep_for(chrono::milliseconds(100));
	}
}


void LifeManagement::runUpdateCarni()
{
	bool nextDestFound = false;
	while (true)
	{
		this->lockListCarni.lock();
		for (list<Carnivorous*>::iterator itCarni = this->listCarni.begin(); itCarni != this->listCarni.end(); itCarni++)
		{
			this->lockListHerbi.lock();
			for (list<Herbivorous*>::iterator itHerbi = this->listHerbi.begin(); itHerbi != this->listHerbi.end(); itHerbi++)
			{
				if (ToolsLifeGame::checkCollision((*itCarni)->getOfVec2f(), (*itHerbi)->getOfVec2f(), 8)) {
					(*itHerbi)->kill();
					
					//this->soundLife->playSoundEatHerbi(-(0.5f - ToolsLifeGame::div((*itHerbi)->getOfVec2f().x, ofGetWidth()) ));
				}
				else {
					//Intelli Move to Herbi 
					if (!nextDestFound &&ToolsLifeGame::checkCollision((*itCarni)->getOfVec2f(), (*itHerbi)->getOfVec2f(), 150))
					{
						(*itCarni)->setNextDesti((*itHerbi)->getOfVec2f());
						nextDestFound = true;
					}
				}
				nextDestFound = false;
			}
			this->lockListHerbi.unlock();
			for (list<Carnivorous*>::iterator itCarniVader = this->listCarni.begin(); itCarniVader != this->listCarni.end(); itCarniVader++)
			{
				if ((*itCarni) != (*itCarniVader) &&
					ToolsLifeGame::checkCollision((*itCarni)->getOfVec2f(), (*itCarniVader)->getOfVec2f(), 4) &&
					(*itCarni)->getSexe() != (*itCarniVader)->getSexe() && this->listHerbi.size() < this->dataLife->limitHerbi)
				{
					(*itCarniVader)->duplication();
				}
			}

			if ((*itCarni)->babyReady()) {
				(*itCarni)->babyBorn();
				Carnivorous * babyCarni = new Carnivorous((*itCarni), this->carnivorImage, this->tools, 0);
				babyCarni->setPosition((*itCarni)->getOfVec2f());
				babyCarni->setAge(1);
				//fprintf(stderr, "Born...\n");
				this->listCarni.push_front(babyCarni);
			}
			if (this->listCarni.size() < 3) {
				for (int i = 0; i < 4; i++) {
					Carnivorous * babyCarni = new Carnivorous(nullptr, this->carnivorImage, this->tools,1);
					babyCarni->setPosition(ToolsLifeGame::getRandomPosition());
					babyCarni->setAge(1);
					this->listCarni.push_front(babyCarni);
				}
			}
		}
		this->lockListCarni.unlock();
		
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void LifeManagement::runUpdatePackPos()
{
	/*while (true)
	{
		for (int i = 0; i < this->tools->listHerPack.size(); i++)
		{
			this->tools->listHerPack[i] = ToolsLifeGame::getRandomPosition(this->tools->listHerPack[i], 100);
		}
		for (int i = 0; i < this->tools->listCarPack.size(); i++)
		{
			this->tools->listCarPack[i] = ToolsLifeGame::getRandomPosition(this->tools->listCarPack[i], 250);
		}
		this_thread::sleep_for(chrono::milliseconds(this->dataLife->speedLifeGame *60));
	}*/
}

void LifeManagement::updateLifeTime()
{
	while (true) {
		this->counterLife += 1;

		//1 Year--------------------------------------------------------
		if ((this->counterLife - ((this->counterLife / 11) * 11)) == 0) {
			//this->vegetUpdate();

			this->lockListTrees.lock();
			for (list<Vegetable*>::iterator itTree = this->listTrees.begin(); itTree != this->listTrees.end();)
			{
				(*itTree)->aging();
				if ((*itTree)->isDead()) {
					delete * itTree;
					(*itTree) = nullptr;
					itTree = this->listTrees.erase(itTree);
				}
				else {
					itTree++;
				}
			}
			this->lockListTrees.unlock();

			this->lockListHerbi.lock();
			for (list<Herbivorous*>::iterator itHerbi = this->listHerbi.begin(); itHerbi != this->listHerbi.end(); )
			{
				(*itHerbi)->aging();
				if ((*itHerbi)->isDead()) {
					delete * itHerbi;
					(*itHerbi) = nullptr;
					itHerbi = this->listHerbi.erase(itHerbi);
				}
				else {
					itHerbi++;
				}				
			}
			this->lockListHerbi.unlock();

			this->lockListCarni.lock();
			for (list<Carnivorous*>::iterator itCarni = this->listCarni.begin(); itCarni != this->listCarni.end(); )
			{
				(*itCarni)->aging();
				if ((*itCarni)->isDead()) {
					delete * itCarni;
					(*itCarni) = nullptr;
					itCarni = this->listCarni.erase(itCarni);
				}
				else {
					itCarni++;
				}
			}
			this->lockListCarni.unlock();
			this->mainServer->sendData("YEAR " + to_string(this->counterLife / 11));
		}

		//Update Anim:::::::::::::::::::::::::::::::::::::::::::::::::
		//Herbi-----------------------
		this->lockListHerbi.lock();
		for (list<Herbivorous*>::iterator itHerbi = this->listHerbi.begin(); itHerbi != this->listHerbi.end(); itHerbi++)
		{
			(*itHerbi)->updateMove();
			(*itHerbi)->updateGestation(2);
		}
		this->lockListHerbi.unlock();

		//Carni---------------------
		this->lockListCarni.lock();
		for (list<Carnivorous*>::iterator itCarni = this->listCarni.begin(); itCarni != this->listCarni.end(); itCarni++)
		{
			(*itCarni)->updateMove();
			(*itCarni)->updateGestation(2);
		}
		this->lockListCarni.unlock();
		//this->testH->updateMove();
		//Speed Life--------------------------------------------
		this_thread::sleep_for(chrono::milliseconds(this->dataLife->speedLifeGame));
	}
}

void LifeManagement::vegetUpdate()
{
	int limitGenTree = 0;
	if (!this->listTrees.empty() && this->listTrees.size() < (this->dataLife->limitTrees / 2)) {
		this->lockListTrees.lock();

		for (list<Vegetable*>::iterator itTree = this->listTrees.begin(); itTree != this->listTrees.end(); itTree++)
		{
			if ((*itTree)->getAge() > 15) {
				Vegetable * tree = new Vegetable(this->vegetalImage);
				tree->setPosition(this->getRandPositionVeget((*itTree)->getOfVec2f(), 85));
				tree->setAge(1);
				if (tree->getOfVec2f().x != 0 && tree->getOfVec2f().y != 0 && limitGenTree < 3) {
					this->listTrees.push_front(tree);
				}
				limitGenTree += 1;
			}
			(*itTree)++;
		}
		this->lockListTrees.unlock();
	}
}

ofVec2f LifeManagement::getRandPositionVeget(ofVec2f pos, int rad)
{
	ofVec2f returnPos;
	returnPos.x = (pos.x + (1 + (rand() % (int)((rad * 2) - 1 + 1)))) - rad;
	returnPos.y = (pos.y + (1 + (rand() % (int)((rad * 2) - 1 + 1)))) - rad;

	for (list<Vegetable*>::iterator itTree = this->listTrees.begin(); itTree != this->listTrees.end(); itTree++)
	{
		int ii = 0;
		while (!this->positionIsFree((*itTree)->getOfVec2f(), returnPos, 0) && ii < 5) {
			returnPos.x = (pos.x + (1 + (rand() % (int)((rad * 2) - 1 + 1)))) - rad;
			ii += 1;
		}
		if (!this->positionIsFree((*itTree)->getOfVec2f(), returnPos, 0)) {
			returnPos.x = 0;
		}
		ii = 0;
		while (!this->positionIsFree((*itTree)->getOfVec2f(), returnPos, 1) && ii < 5) {
			returnPos.y = (pos.y + (1 + (rand() % (int)((rad * 2) - 1 + 1)))) - rad;
			ii += 1;
		}
		if (!this->positionIsFree((*itTree)->getOfVec2f(), returnPos, 1)) {
			returnPos.y = 0;
		}
	}

	return returnPos;
}

bool LifeManagement::positionIsFree(ofVec2f pos1, ofVec2f pos2, char xy)
{
	if (xy == 0) {
		return !ToolsLifeGame::checkCollision(pos1, pos2, 4) && pos2.x < ofGetWidth() && pos2.x > 0;
	}
	else {
		return !ToolsLifeGame::checkCollision(pos1, pos2, 4) && pos2.y < ofGetHeight() && pos2.y > 0;
	}
}



void LifeManagement::update()
{

}

void LifeManagement::draw()
{
	
	this->mapLife->draw();

	//Trees----------------------
	this->lockListTrees.lock();
	for (list<Vegetable*>::iterator itTree = this->listTrees.begin(); itTree != this->listTrees.end(); itTree++)
	{
		(*itTree)->draw();
	}
	this->lockListTrees.unlock();

	//Herbi---------------------
	this->lockListHerbi.lock();
	for (list<Herbivorous*>::iterator itHerbi = this->listHerbi.begin(); itHerbi != this->listHerbi.end(); itHerbi++)
	{
		(*itHerbi)->draw();
	}
	this->lockListHerbi.unlock();

	//Carni---------------------
	this->lockListCarni.lock();
	for (list<Carnivorous*>::iterator it = this->listCarni.begin(); it != this->listCarni.end(); it++)
	{
		(*it)->draw();
	}
	this->lockListCarni.unlock();

	//testH->draw();
	//Data show------------------
	ofSetColor(255, 255, 255, 255.0);
	this->dataToScreenLeft.str("");
	this->dataToScreenLeft << "Mois : " << (this->counterLife - ((this->counterLife / 11) * 11)) + 1 << "\nAns : " << (this->counterLife / 11) << std::endl;
	ofDrawBitmapString(this->dataToScreenLeft.str(), 5, 14);

}

LifeManagement::~LifeManagement()
{
}
