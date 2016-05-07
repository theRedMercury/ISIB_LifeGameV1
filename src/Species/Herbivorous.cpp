#include "Herbivorous.h"

Herbivorous::Herbivorous(Herbivorous * mama, ofImage * img, DataLife * tool, SoundLife * sound, int numP)
{
	this->mother = mama;
	this->imgSprite = img;
	this->dataLife = tool;
	this->soundL = sound;

	this->ageDead = (unsigned char)(this->dataLife->ageDeadHerbi + ((rand() % ((2* this->dataLife->ageRandHerbi)+1)) - this->dataLife->ageRandHerbi));
	this->radiusC = (((this->age / 42.0f) + 1)* ToolsLifeGame::RadiusC) / 1.2f;

	this->visionDist = this->dataLife->visionStartHerbi;
	this->visionAnlge = this->dataLife->visionAngleHerbi;
	this->showVision = this->dataLife->visionShowHerbi;

	this->setEatFound(false);
	if (this->mother != nullptr) {
		this->x1 = this->mother->getOfVec2f();
		this->x2 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 10 + this->mother->getAge() / 10.0f);
		this->x3 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 8 + this->mother->getAge() / 10.0f);
		this->x4 = ToolsLifeGame::getRandomPosition(this->x3, 150);
	}
	else {
		this->x1 = ToolsLifeGame::getRandomPosition();
		this->x2 = ToolsLifeGame::getRandomPosition(this->x1, 250);
		this->x3 = ToolsLifeGame::getRandomPosition(this->x2, 250);
		this->x4 = ToolsLifeGame::getRandomPosition(this->x3, 150);
	}

	if(this->imgSprite==nullptr) {
		this->shape->setHexColor(0x2e2f87);
		this->shape->circle(this->posXY.x, this->posXY.y, this->radiusC);
	}	


	

	this->old.x = this->posXY.x;
	this->old.y = this->posXY.y;
	this->circleDetect = new ofPath();
	this->circleDetect->setColor(ofColor(46, 46, 216, 50));
	this->circleDetect->circle(this->posXY.x, this->posXY.y, 75);
	this->vision = new ofPath();
	this->vision->setColor(ofColor(200, 200, 216, 50));
	this->vision->arc(this->posXY.x, this->posXY.y, 75, 75, 90, 180);
	this->vision->setArcResolution(600);
}



void Herbivorous::aging()
{
	
	this->visionDist += 1.0f;
	if (this->visionDist > this->dataLife->visionMaxHerbi) {
		this->visionDist -= 1.0f;
	}

	this->age += 1;
	this->radiusC = (((this->age / 42.0f) + 1)* ToolsLifeGame::RadiusC) / 1.2f;
	if (this->age >= this->ageDead) {
		this->age = this->ageDead;
		this->dead = true;
	}
}


void Herbivorous::updateAnimation()
{
	//Follow Mother----------------------------------
	if (this->mother != nullptr && this->age <  this->dataLife->weaningYearHerbi) {

		this->percentAnim += 0.025*this->speedMov;
		this->posXY.x = getPointPercent(getPointPercent(this->x1.x, this->x2.x, this->percentAnim), getPointPercent(this->x2.x, this->x3.x, this->percentAnim), this->percentAnim);
		this->posXY.y = getPointPercent(getPointPercent(this->x1.y, this->x2.y, this->percentAnim), getPointPercent(this->x2.y, this->x3.y, this->percentAnim), this->percentAnim);

		if (this->percentAnim >= 1.0) {
			this->x1 = this->posXY;
			this->x2 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 10+this->mother->getAge()/8.0f);
			this->x3 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 8 + this->mother->getAge() / 10.0f);
			this->x4 = ToolsLifeGame::getRandomPosition(this->x3,50);
			this->setEatFound(false);
			this->percentAnim = 0;
		}
	}
	else {
		this->mother = nullptr;
		float dist = (1.0 / (abs(sqrt(pow(this->x1.x - this->x4.x, 2) + pow(this->x1.x - this->x4.x, 2))) + 0.001f)) / 4.0f;
		this->percentAnim += dist*this->speedMov;
		/*if (dist > 0.003) {
			this->percentAnim += 0.002*this->speedMov;
		}
		else {
			this->percentAnim += dist*this->speedMov;
		}*/

		float xa1 = getPointPercent(getPointPercent(this->x1.x, this->x2.x, this->percentAnim), getPointPercent(this->x2.x, this->x3.x, this->percentAnim), this->percentAnim);
		float ya1 = getPointPercent(getPointPercent(this->x1.y, this->x2.y, this->percentAnim), getPointPercent(this->x2.y, this->x3.y, this->percentAnim), this->percentAnim);
		float xa2 = getPointPercent(getPointPercent(this->x2.x, this->x3.x, this->percentAnim), getPointPercent(this->x3.x, this->x4.x, this->percentAnim), this->percentAnim);
		float ya2 = getPointPercent(getPointPercent(this->x2.y, this->x3.y, this->percentAnim), getPointPercent(this->x3.y, this->x4.y, this->percentAnim), this->percentAnim);

		this->old.x = this->posXY.x;
		this->old.y = this->posXY.y;

		this->posXY.x = getPointPercent(xa1, xa2, this->percentAnim);
		this->posXY.y = getPointPercent(ya1, ya2, this->percentAnim);
		this->angl = atan2f(this->posXY.y - this->old.y, this->posXY.x - this->old.x)* (180.0f / PI);

		this->vision->clear();
		this->vision->arc(this->posXY.x, this->posXY.y, this->visionDist, this->visionDist, this->angl - (this->visionAnlge/2.0f), this->angl + (this->visionAnlge/2.0f));
		this->circleDetect->clear();
		this->circleDetect->circle(this->posXY.x, this->posXY.y, 75);

		if (this->percentAnim >= 1.0) {
			this->x1 = this->posXY;
			this->x2 = ToolsLifeGame::getRandomPosition(this->x1, 45);
			this->x3 = ToolsLifeGame::getRandomPosition(this->x2, 120);
			this->x4 = ToolsLifeGame::getRandomPosition(this->x3, 150);
			this->setEatFound(false);
			this->percentAnim = 0;
		}
	}
	this->shape->clear();
	this->shape->setColor(ofColor(46, 47, 150.0f + this->energy));
	this->shape->circle(this->posXY.x, this->posXY.y, this->radiusC);

}

void Herbivorous::update()
{
	bool eatFound = false;
	float eatDist = this->visionDist + 10.0f;
	ofVec2f dest;

	if (this->energy > 10) {
		this->energy -= 5;
	}
	this->setWantEat(this->energy < 75);

	if (this->mother == nullptr) {
		//TREE MANAGE==============================================
		this->dataLife->lockListTrees.lock();
		for (list<Vegetable*>::iterator itTree = this->dataLife->listTrees.begin(); itTree != this->dataLife->listTrees.end(); )
		{
			//In Vision=================================
			if (ToolsLifeGame::getDistance(this->posXY, (*itTree)->getOfVec2f()) < eatDist && (*itTree)->getAge() > 5 && !this->getEatFound() && this->getWantEat() &&
				ToolsLifeGame::arCCollision(this->posXY, this->angl, this->visionAnlge, this->visionDist, (*itTree)->getOfVec2f())) {
				eatFound = true;
				eatDist = ToolsLifeGame::getDistance(this->posXY, (*itTree)->getOfVec2f());
				dest = (*itTree)->getOfVec2f();
			}

			//Eat Tree=================================
			if (this->getEnergy() < 90.0f && ToolsLifeGame::checkCollision(this->getOfVec2f(), (*itTree)->getOfVec2f(), 8)) {
				this->eating(5 + (*itTree)->getAge() / 10);
				(*itTree)->kill();
				delete * itTree;
				(*itTree) = nullptr;

				this->soundL->playSoundEatVeg(-(0.5f - ToolsLifeGame::div(this->getOfVec2f().x, ofGetWindowWidth())));
				itTree = this->dataLife->listTrees.erase(itTree);
			}
			else {
				itTree++;
			}

		}
		this->dataLife->lockListTrees.unlock();

		//Detect Carni==============================================
		/*this->dataLife->lockListCarni.lock();
		for (list<Carnivorous*>::iterator itCarniVader = this->dataLife->listCarni.begin(); itCarniVader != this->dataLife->listCarni.end(); itCarniVader++)
		{
			//In Circle=================================
			if (ToolsLifeGame::checkCollision(this->posXY, (*itCarniVader)->getOfVec2f(), this->detectCircleSize)) {
				if (ToolsLifeGame::getDistance(this->posXY, (*itCarniVader)->getOfVec2f()) <= 15.0f) {
					this->speedMov += 0.5f;
				}
			}
		}
		this->dataLife->lockListCarni.unlock();*/
		//Reporduction==============================================
		for (list<Herbivorous*>::iterator itHerbiVader = this->dataLife->listHerbi.begin(); itHerbiVader != this->dataLife->listHerbi.end(); itHerbiVader++)
		{
			if (this != (*itHerbiVader) &&
				ToolsLifeGame::checkCollision(this->getOfVec2f(), (*itHerbiVader)->getOfVec2f(), 4) &&
				this->getSexe() != (*itHerbiVader)->getSexe() && this->dataLife->listHerbi.size() < this->dataLife->limMaxCarni)
			{
				(*itHerbiVader)->duplication(this->dataLife->gestationYearHerbi);
			}
		}
		if (this->babyReady()) {
			this->babyBorn();
			Herbivorous * babyHerbi = new Herbivorous(this, this->imgSprite, this->dataLife, this->soundL);
			babyHerbi->setPosition(this->getOfVec2f());

			this->dataLife->listHerbi.push_front(babyHerbi);
		}

		//===========================================
		if (eatFound && !this->getEatFound()) {
			this->calNewPath(dest);
			this->setEatFound(true);
		}
	}
}


void Herbivorous::calNewPath(ofVec2f d)
{
	this->x1 = this->posXY;
	this->x2 = ToolsLifeGame::getHalfPath(this->x1, d);
	this->x3 = ToolsLifeGame::getHalfPath(this->x2, d);
	this->x4 = d;
	this->percentAnim = 0;
}

void Herbivorous::draw()
{
	/*ofDrawCircle(this->x1.x, this->x1.y, 2);
	ofDrawCircle(this->x2.x, this->x2.y, 2);
	ofDrawCircle(this->x3.x, this->x3.y, 2);
	ofDrawCircle(this->x4.x, this->x4.y, 2);*/
	
	if (!this->dead) {
		
		//this->shape->draw();
		if (this->imgSprite != nullptr) {
			if (this->age > 50) {
				ofSetColor(255 - (this->age/2), 255 - (this->age / 2), 255 - (this->age / 2));
			}
			else {
				ofSetColor(255, 255, 255);
			}
			this->imgSprite->draw(this->posXY.x - ((this->radiusC*3) / 2.0f), (this->posXY.y - (this->radiusC*3)/2.0f), this->radiusC*3, this->radiusC*3);
		}

		else {
			//this->circleDetect->draw();
			if (this->showVision && this->mother == nullptr) {
				this->vision->draw();
			}
			this->shape->draw();
		}
		if (this->pregnancy > 1 && !this->getSexe() && this->getPregnant()) {
			ofSetColor(255, 255, 255);
			ofDrawCircle(this->posXY, 2);
		}
		
	}
}

Herbivorous::~Herbivorous()
{
	this->mother = nullptr;
	this->dataLife = nullptr;
}
