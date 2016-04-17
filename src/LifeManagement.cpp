#include "LifeManagement.h"

LifeManagement::LifeManagement()
{
	srand(time(NULL));
	this->runAllThread = true;
	this->counterLife = 0;

	this->dataLife = new DataLife();
	this->mainServer = new SocketServer(this->dataLife);
	this->soundLife = new SoundLife(this->dataLife->soundMainLevel);
	this->mapLife = new Map(this->dataLife);


	this->herbivorImage = new ofImage();
	if (this->herbivorImage->loadImage("herbi.png")) {
		this->herbivorImage->allocate(42, 39, OF_IMAGE_COLOR_ALPHA);
	}
	else {
		delete (this->herbivorImage);
		this->herbivorImage = nullptr;
	}
	

	this->carnivorImage = new ofImage();
	if (this->carnivorImage->loadImage("carni.png")) {
		this->carnivorImage->allocate(67, 59, OF_IMAGE_COLOR_ALPHA);
	}
	else {
		delete (this->carnivorImage);
		this->carnivorImage = nullptr;
	}

}

void LifeManagement::setInvasiv()
{
	this->dataLife->launchInvade = true;
}
void LifeManagement::init()
{
	for (int i = 0; i < 25; i++) {
		Herbivorous * herbi = new Herbivorous(nullptr, this->herbivorImage, this->dataLife, this->soundLife, 0);
		this->dataLife->listHerbi.push_back(herbi);
	}

	for (int i = 0; i < 10; i++) {
		Carnivorous * carni = new Carnivorous(nullptr, this->carnivorImage, this->dataLife, this->soundLife, 0);
		this->dataLife->listCarni.push_back(carni);
	}

	this->lifeTimeThread = thread(&LifeManagement::updateLifeTime, this);
	
	this->threadUpdateAnimation = thread(&LifeManagement::runUpdateAnimation, this);

	this->threadUpdateHerbi = thread(&LifeManagement::runUpdateHerbi, this);
	this->threadUpdateCarni = thread(&LifeManagement::runUpdateCarni, this);
	this->threadUpdateInvade = thread(&LifeManagement::runUpdateInvade, this);
	//this->threadUpdatePack = thread(&LifeManagement::runUpdatePackPos, this);
}


void LifeManagement::runUpdateHerbi()
{
	while (this->runAllThread)
	{
		this->dataLife->lockListHerbi.lock();
		for (list<Herbivorous*>::iterator itHerbi = this->dataLife->listHerbi.begin(); itHerbi != this->dataLife->listHerbi.end(); itHerbi++)
		{
			(*itHerbi)->update();
			if (this->dataLife->listHerbi.size() < this->dataLife->minHerbi) {
				for (int i = 0; i < this->dataLife->minHerbi; i++) {
					Herbivorous * babyHerbi = new Herbivorous(nullptr, this->herbivorImage, this->dataLife, this->soundLife, 0);
					this->dataLife->listHerbi.push_front(babyHerbi);
				}
			}
		}
		this->dataLife->lockListHerbi.unlock();
		this_thread::sleep_for(chrono::milliseconds(500));
		this->mainServer->sendData("Tree " + to_string(this->dataLife->listTrees.size()));
		this_thread::sleep_for(chrono::milliseconds(10));
		this->mainServer->sendData("Herbi " + to_string(this->dataLife->listHerbi.size()));
	}
}


void LifeManagement::runUpdateCarni()
{
	while (this->runAllThread)
	{
		this->dataLife->lockListCarni.lock();
		for (list<Carnivorous*>::iterator itCarni = this->dataLife->listCarni.begin(); itCarni != this->dataLife->listCarni.end(); itCarni++)
		{
			(*itCarni)->update();
			if (this->dataLife->listHerbi.size() < this->dataLife->minCarni) {
				for (int i = 0; i <  this->dataLife->minCarni; i++) {
					Carnivorous * babyCarni = new Carnivorous(nullptr, this->carnivorImage, this->dataLife, this->soundLife, 0);
					this->dataLife->listCarni.push_front(babyCarni);
				}
			}
		}
		this->dataLife->lockListCarni.unlock();
		this_thread::sleep_for(chrono::milliseconds(250));
		this->mainServer->sendData("Carni " + to_string(this->dataLife->listCarni.size()));
	}
}

void LifeManagement::runUpdateInvade()
{
	while (this->runAllThread)
	{
		//While not lauchn Invade
		while (!this->dataLife->launchInvade) {
			this->dataLife->lockListInva.lock();
			for (list<Invasive*>::iterator itInvad = this->dataLife->listInva.begin(); itInvad != this->dataLife->listInva.end(); itInvad++)
			{
				(*itInvad)->update();
			}
			this->dataLife->lockListInva.unlock();
			this_thread::sleep_for(chrono::milliseconds(500));
			this->mainServer->sendData("Invad " + to_string(this->dataLife->listInva.size()));
		}

		//Add Invade
		this->soundLife->playSoundStartInvade();
		for (int i = 0; i < 1000; i++) {
			if (this->dataLife->listInva.size() < this->dataLife->limitInvade) {
				Invasive * invad = new Invasive(this->herbivorImage, this->dataLife, 0);
				this->dataLife->listInva.push_back(invad);
			}
		}
		cout << this->dataLife->listInva.size() << endl;
		this->dataLife->launchInvade = false;
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
	while (this->runAllThread) {
		this->counterLife += 1;

		if ((this->counterLife - ((this->counterLife / 11) * 11)) == 0) {
			//1 Year--------------------------------------------------------

			this->dataLife->lockListHerbi.lock();
			for (list<Herbivorous*>::iterator itHerbi = this->dataLife->listHerbi.begin(); itHerbi != this->dataLife->listHerbi.end(); )
			{
				(*itHerbi)->aging();
				(*itHerbi)->updateGestation(12);
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
				(*itCarni)->updateGestation(12);
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

			this->dataLife->lockListInva.lock();
			for (list<Invasive*>::iterator itInvad = this->dataLife->listInva.begin(); itInvad != this->dataLife->listInva.end();)
			{
				(*itInvad)->aging();
				if ((*itInvad)->isDead()) {
					delete * itInvad;
					(*itInvad) = nullptr;
					itInvad = this->dataLife->listInva.erase(itInvad);
				}
				else {
					itInvad++;
				}
			}
			this->dataLife->lockListInva.unlock();
			this->mainServer->sendData("YEAR " + to_string(this->counterLife / 11));
		}

		//Speed Life--------------------------------------------
		this_thread::sleep_for(chrono::milliseconds(this->dataLife->speedLifeGame));
	}
}

void LifeManagement::runUpdateAnimation()
{
	while (this->runAllThread)
	{
		//Herbi-----------------------
		this->dataLife->lockListHerbi.lock();
		for (list<Herbivorous*>::iterator itHerbi = this->dataLife->listHerbi.begin(); itHerbi != this->dataLife->listHerbi.end(); itHerbi++)
		{
			(*itHerbi)->updateAnimation();
		}
		this->dataLife->lockListHerbi.unlock();

		//Carni---------------------
		this->dataLife->lockListCarni.lock();
		for (list<Carnivorous*>::iterator itCarni = this->dataLife->listCarni.begin(); itCarni != this->dataLife->listCarni.end(); itCarni++)
		{
			(*itCarni)->updateAnimation();
		}
		this->dataLife->lockListCarni.unlock();

		//Invase----------------------
		this->dataLife->lockListInva.lock();
		for (list<Invasive*>::iterator itInva = this->dataLife->listInva.begin(); itInva != this->dataLife->listInva.end(); itInva++)
		{
			(*itInva)->updateAnimation();
		}
		this->dataLife->lockListInva.unlock();

		//Animation speed
		this_thread::sleep_for(chrono::milliseconds(35));
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

	//Invad---------------------
	this->dataLife->lockListInva.lock();
	for (list<Invasive*>::iterator itInvad = this->dataLife->listInva.begin(); itInvad != this->dataLife->listInva.end(); itInvad++)
	{
		(*itInvad)->draw();
	}
	this->dataLife->lockListInva.unlock();

	//Carni---------------------
	this->dataLife->lockListCarni.lock();
	for (list<Carnivorous*>::iterator itCarni = this->dataLife->listCarni.begin(); itCarni != this->dataLife->listCarni.end(); itCarni++)
	{
		(*itCarni)->draw();
	}
	this->dataLife->lockListCarni.unlock();

	//Data show------------------
	ofSetColor(255, 255, 255, 255.0);
	this->dataToScreenLeft.str("");
	this->dataToScreenLeft << "Mois : " << (this->counterLife - ((this->counterLife / 11) * 11)) + 1 << "\nAns : " << (this->counterLife / 11) << std::endl;
	ofDrawBitmapString(this->dataToScreenLeft.str(), 5, 14);
}

LifeManagement::~LifeManagement()
{
	delete this->mainServer;
	delete this->soundLife;
	delete this->dataLife;
	delete this->mapLife;

	delete this->herbivorImage;
	delete this->carnivorImage;
	delete this->invasiveImage;
}
