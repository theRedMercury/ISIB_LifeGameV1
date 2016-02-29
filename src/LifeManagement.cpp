#include "LifeManagement.h"

LifeManagement::LifeManagement()
{
	this->dataLife = new DataLife();
	this->mainServer = new SocketServer(this->dataLife);
	this->soundLife = new SoundLife(0.0);

	this->mapLife = new Map(this->dataLife);

	this->counterLife = 0;
	this->tools = new ToolsLifeGame();

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

	for (int i = 0; i < 500; i++) {
		Herbivorous * herbi = new Herbivorous(nullptr, this->herbivorImage, this->dataLife,0);
		//herbi->setPosition(ToolsLifeGame::getRandomPosition(this->tools->listHerPack.at(0),1));
		herbi->setAge(1);
		this->dataLife->listHerbi.push_back(herbi);
	}
	for (int i = 0; i < 20; i++) {
		Herbivorous * herbi = new Herbivorous(nullptr, this->herbivorImage, this->dataLife,1);
		//herbi->setPosition(ToolsLifeGame::getRandomPosition(this->tools->listHerPack.at(1), 1));
		herbi->setAge(1);
		this->dataLife->listHerbi.push_back(herbi);
	}
	

	for (int i = 0; i < 500; i++) {
		Carnivorous * carni = new Carnivorous(nullptr, this->carnivorImage, this->dataLife,0);
		//carni->setPosition(ToolsLifeGame::getRandomPosition(this->tools->listCarPack.at(0), 1));
		carni->setAge(i);
		this->dataLife->listCarni.push_back(carni);
	}
	for (int i = 0; i < 5; i++) {
		Carnivorous * carni = new Carnivorous(nullptr, this->carnivorImage, this->dataLife,1);
		//carni->setPosition(ToolsLifeGame::getRandomPosition(this->tools->listCarPack.at(1), 1));
		carni->setAge(i);
		this->dataLife->listCarni.push_back(carni);
	}

	this->lifeTimeThread = thread(&LifeManagement::updateLifeTime, this);

	
	//this->threadUpdateHerbi = thread(&LifeManagement::runUpdateHerbi, this);
	//this->threadUpdateCarni = thread(&LifeManagement::runUpdateCarni, this);

	//this->threadUpdatePack = thread(&LifeManagement::runUpdatePackPos, this);
}



void LifeManagement::runUpdateHerbi()
{
	/*bool nextDestFound = false;
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
	}*/
}


void LifeManagement::runUpdateCarni()
{
	/*bool nextDestFound = false;
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
	}*/
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

			//this->lockListTrees.lock();
			/*for (list<Vegetable*>::iterator itTree = this->listTrees.begin(); itTree != this->listTrees.end();)
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
			this->lockListTrees.unlock();*/

			this->dataLife->lockListHerbi.lock();
			for (list<Herbivorous*>::iterator itHerbi = this->dataLife->listHerbi.begin(); itHerbi != this->dataLife->listHerbi.end(); )
			{
				(*itHerbi)->aging();
				if ((*itHerbi)->isDead()) {
					delete * itHerbi;
					(*itHerbi) = nullptr;
					itHerbi = this->dataLife->listHerbi.erase(itHerbi);
				}
				else {
					itHerbi++;
				}				
			}
			this->dataLife->lockListHerbi.unlock();

			this->dataLife->lockListCarni.lock();
			for (list<Carnivorous*>::iterator itCarni = this->dataLife->listCarni.begin(); itCarni != this->dataLife->listCarni.end(); )
			{
				(*itCarni)->aging();
				if ((*itCarni)->isDead()) {
					delete * itCarni;
					(*itCarni) = nullptr;
					itCarni = this->dataLife->listCarni.erase(itCarni);
				}
				else {
					itCarni++;
				}
			}
			this->dataLife->lockListCarni.unlock();
			this->mainServer->sendData("YEAR " + to_string(this->counterLife / 11));
		}

		//Update Anim:::::::::::::::::::::::::::::::::::::::::::::::::
		//Herbi-----------------------
		this->dataLife->lockListHerbi.lock();
		for (list<Herbivorous*>::iterator itHerbi = this->dataLife->listHerbi.begin(); itHerbi != this->dataLife->listHerbi.end(); itHerbi++)
		{
			(*itHerbi)->updateMove();
			(*itHerbi)->updateGestation(2);
		}
		this->dataLife->lockListHerbi.unlock();

		//Carni---------------------
		this->dataLife->lockListCarni.lock();
		for (list<Carnivorous*>::iterator itCarni = this->dataLife->listCarni.begin(); itCarni != this->dataLife->listCarni.end(); itCarni++)
		{
			(*itCarni)->updateMove();
			(*itCarni)->updateGestation(2);
		}
		this->dataLife->lockListCarni.unlock();
		//this->testH->updateMove();
		//Speed Life--------------------------------------------
		this_thread::sleep_for(chrono::milliseconds(this->dataLife->speedLifeGame));
	}
}






void LifeManagement::update()
{

}

void LifeManagement::draw()
{
	
	this->mapLife->draw();
	

	//Herbi---------------------
	this->dataLife->lockListHerbi.lock();
	for (list<Herbivorous*>::iterator itHerbi = this->dataLife->listHerbi.begin(); itHerbi != this->dataLife->listHerbi.end(); itHerbi++)
	{
		(*itHerbi)->draw();
	}
	this->dataLife->lockListHerbi.unlock();

	//Carni---------------------
	this->dataLife->lockListCarni.lock();
	for (list<Carnivorous*>::iterator it = this->dataLife->listCarni.begin(); it != this->dataLife->listCarni.end(); it++)
	{
		(*it)->draw();
	}
	this->dataLife->lockListCarni.unlock();

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
