#include "Carnivorous.h"


Carnivorous::Carnivorous(Carnivorous * mama, ofImage * img, DataLife * data, SoundLife * sound, int numP)
{
	this->mother = mama;
	this->dataLife = data;
	this->soundL = sound;
	this->ageDead = (unsigned char)(this->dataLife->ageDeadCarni + ((rand() % ((2 * this->dataLife->ageRandCarni) + 1)) - this->dataLife->ageRandCarni));
	this->squarHW = (((this->age / 42.0f) + 1)* ToolsLifeGame::SquarHW) / 1.2f;

	this->visionDist = this->dataLife->visionStartCarni;
	this->visionAnlge = this->dataLife->visionAngleCarni;
	this->showVision = this->dataLife->visionShowCarni;

	this->setWantDuplicate(true);
	//Follow the mother
	if (this->mother != nullptr) {
		
		this->posXY = this->mother->getOfVec2f();
		this->x1 = this->mother->getOfVec2f();
		this->x2 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 10 + this->mother->getAge() / 10.0f);
		this->x3 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 8 + this->mother->getAge() / 10.0f);
	}
	else {
		this->x1 = ToolsLifeGame::getRandomPosition();
		this->x2 = ToolsLifeGame::getRandomPosition(this->x1, 250);
		this->x3 = ToolsLifeGame::getRandomPosition(this->x2, 250);
	}

	//Image or Shape
	if (img != nullptr) {
		this->imgSprite = img;
	}
	else {
		this->shape->setHexColor(0x872f30);
		this->shape->rectangle(this->posXY.x - (this->squarHW / 2.0f), this->posXY.y - (this->squarHW / 2.0f), this->squarHW, this->squarHW);
	}


	this->old.x = this->posXY.x;
	this->old.y = this->posXY.y;
	this->circleDetect = new ofPath();
	this->circleDetect->setColor(ofColor(216, 46, 46, 50));
	this->circleDetect->circle(this->posXY.x, this->posXY.y, this->detectCircleSize);
	this->vision = new ofPath();
	this->vision->setColor(ofColor(216, 200, 200, 50));
	this->vision->arc(this->posXY.x, this->posXY.y, 75, 75, 90, 180);

}


void Carnivorous::aging()
{
	this->visionDist += 1.0f;
	if(this->visionDist > this->dataLife->visionMaxCarni) {
		this->visionDist -= 1.0f;
	}

	this->age += 1;
	this->squarHW = (((this->age / 42.0f) + 1)* ToolsLifeGame::SquarHW) / 1.2f;
	if (this->age >= this->ageDead) {
		this->age -= 1;
		this->dead = true;
	}
}


void Carnivorous::updateAnimation()
{
	//Follow Mother----------------------------------
	if (this->mother != nullptr && this->age <  this->dataLife->weaningYearCarni) {

		this->percentAnim += 0.025*this->speedMov;	
		this->posXY.x = getPointPercent(getPointPercent(this->x1.x, this->x2.x, this->percentAnim), getPointPercent(this->x2.x, this->x3.x, this->percentAnim), this->percentAnim);
		this->posXY.y = getPointPercent(getPointPercent(this->x1.y, this->x2.y, this->percentAnim), getPointPercent(this->x2.y, this->x3.y, this->percentAnim), this->percentAnim);

		if (this->percentAnim >0.99f) {
			this->x1 = this->posXY;
			this->x2 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 10 + this->mother->getAge() / 8.0f);
			this->x3 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 8 + this->mother->getAge() / 10.0f);
			this->setEatFound(false);
			this->percentAnim = 0;
		}
	}
	else {
		this->mother = nullptr;
		float dist = (1.0 / (abs(sqrt(pow(this->x2.x - this->x3.x, 2) + pow(this->x2.x - this->x3.x, 2)))+0.001f)) / 4.0f;
		this->percentAnim += dist*this->speedMov;

		

		/*if (dist > 0.0035) {
			this->percentAnim += 0.0025*this->speedMov;
		}
		else {
			this->percentAnim += dist*this->speedMov;
		}*/

		this->old.x = this->posXY.x;
		this->old.y = this->posXY.y;

		this->posXY.x = getPointPercent(getPointPercent(this->x1.x, this->x2.x, this->percentAnim), getPointPercent(this->x2.x, this->x3.x, this->percentAnim), this->percentAnim);
		this->posXY.y = getPointPercent(getPointPercent(this->x1.y, this->x2.y, this->percentAnim), getPointPercent(this->x2.y, this->x3.y, this->percentAnim), this->percentAnim);

		//Look the Herbi Target
		if (this->herbiTarget != nullptr && !this->herbiTarget->isDead()) {
			this->angl = atan2f(this->herbiTarget->getOfVec2f().y - this->old.y, this->herbiTarget->getOfVec2f().x - this->old.x)* (180.0f / PI);
		}
		else {
			this->angl = atan2f(this->posXY.y - this->old.y, this->posXY.x - this->old.x)* (180.0f / PI);
		}

		this->vision->clear();
		this->vision->arc(this->posXY.x, this->posXY.y, this->visionDist, this->visionDist, this->angl - (this->visionAnlge/2.0f), this->angl + (this->visionAnlge/2.0f));
		this->circleDetect->clear();
		this->circleDetect->circle(this->posXY.x, this->posXY.y, this->detectCircleSize);
		
		
		if (this->percentAnim >= 1.0f) {
			//cout << this->percentAnim << endl;
			this->x1 = this->posXY;
			this->x2 = ToolsLifeGame::getRandomPosition(this->x1, 120);
			this->x3 = ToolsLifeGame::getRandomPosition(this->x2, 150);
			this->setEatFound(false);
			this->percentAnim = 0.0f;
		}

		//Update Final destination
		if (this->getEatLock() && this->herbiTarget != nullptr && !this->herbiTarget->isDead()) {
			this->x3 = this->herbiTarget->getOfVec2f();
		}
	}
	this->shape->clear();
	this->shape->setColor(ofColor(150.0f+ this->energy, 47, 48));
	this->shape->rectangle(this->posXY.x - (this->squarHW / 2.0f), this->posXY.y - (this->squarHW / 2.0f), this->squarHW, this->squarHW);

}

void Carnivorous::update()
{
	if (this->herbiTarget!=nullptr && 
		((this->herbiTarget->getOfVec2f().x >(float)ofGetWindowWidth() + 35.0f || this->herbiTarget->getOfVec2f().x < -35.0f || this->herbiTarget->getOfVec2f().y >(float)ofGetWindowHeight() + 35.0f || this->herbiTarget->getOfVec2f().y < -35.0f)
			|| (ToolsLifeGame::arCCollision(this->posXY, this->angl, this->visionAnlge, this->visionDist, this->herbiTarget->getOfVec2f())))) {
		this->herbiTarget = nullptr;
		this->setEatLock(false);
	}

	if (this->carniTarget != nullptr && 
		(this->carniTarget->getOfVec2f().x >(float)ofGetWindowWidth() + 35.0f || this->carniTarget->getOfVec2f().x < -35.0f || this->carniTarget->getOfVec2f().y >(float)ofGetWindowHeight() + 35.0f || this->carniTarget->getOfVec2f().y < -35.0f)) {
		this->carniTarget = nullptr;
		this->setEatLock(false);
		this->setWantDuplicate(true);
	}
	/*if (this->posXY.x >(float)ofGetWindowWidth() || this->posXY.x < 0.0f || this->posXY.y >(float)ofGetWindowHeight() || this->posXY.y < 0.0f) {
		cout << "ERROR  x:" << this->posXY.x << "  y:" << this->posXY.y << "    H:" << this->herbiTarget << " X:" << this->herbiTarget->getOfVec2f().x << endl;
	}*/

	//Update Param====================
	if (this->visionDist > 275.0f) {
		this->visionDist -= 1.0f;
	}
	if (this->energy > 1.0f) {
		this->energy -= 5.0f;
	}
	this->setWantEat(this->energy < 55.0f);
	
	this->setEatFound(false);

	float eatDist = this->visionDist;

	if (this->mother == nullptr) {
		//Eat Invasive===================================
		this->dataLife->lockListInva.lock();
		for (list<Invasive*>::iterator itInva = this->dataLife->listInva.begin(); itInva != this->dataLife->listInva.end();)
		{
			if (ToolsLifeGame::checkCollision(this->getOfVec2f(), (*itInva)->getOfVec2f(), 4)) {
				this->eating(1.5f);
				delete * itInva;
				(*itInva) = nullptr;
				itInva = this->dataLife->listInva.erase(itInva);
			}
			else {
				itInva++;
			}
		}
		this->dataLife->lockListInva.unlock();

		//Herbi Eating==============================================
		this->dataLife->lockListHerbi.lock();
		for (list<Herbivorous*>::iterator itHerbi = this->dataLife->listHerbi.begin(); itHerbi != this->dataLife->listHerbi.end(); )
		{
			//In Vision=================================
			if (this->getWantEat() &&
				ToolsLifeGame::arCCollision(this->posXY, this->angl, this->visionAnlge, this->visionDist, (*itHerbi)->getOfVec2f()) &&
				ToolsLifeGame::getDistance(this->posXY, (*itHerbi)->getOfVec2f()) < eatDist)
			{
				this->herbiTarget = (Animal *)(*itHerbi);
				this->setEatFound(true);
				eatDist = ToolsLifeGame::getDistance(this->posXY, this->herbiTarget->getOfVec2f());
			}

			//Eat Herbi=================================
			if (this->getWantEat() && ToolsLifeGame::checkCollision(this->getOfVec2f(), (*itHerbi)->getOfVec2f(), 7)) {
				this->eating(25 + ((*itHerbi)->getAge() / 10));
				if (this->herbiTarget == (*itHerbi)) {
					this->herbiTarget = nullptr;
					this->setEatLock(false);
				}
				delete * itHerbi;
				(*itHerbi) = nullptr;
				this->soundL->playSoundEatHerbi(-(0.5f - ToolsLifeGame::div(this->getOfVec2f().x, ofGetWindowWidth())));
				itHerbi = this->dataLife->listHerbi.erase(itHerbi);
			}
			else {
				itHerbi++;
			}
		}
		this->dataLife->lockListHerbi.unlock();

		//Reporduction========================================
		for (list<Carnivorous*>::iterator itCarniVader = this->dataLife->listCarni.begin(); itCarniVader != this->dataLife->listCarni.end(); itCarniVader++)
		{
			if (this - getWantDuplicate() && ToolsLifeGame::checkCollision(this->posXY, (*itCarniVader)->getOfVec2f(), this->detectCircleSize) && this->getSexe() != (*itCarniVader)->getSexe()) {
				this->carniTarget = (Animal *)(*itCarniVader);
				this->setWantDuplicate(false);
			}
			if (this != (*itCarniVader) &&
				ToolsLifeGame::checkCollision(this->getOfVec2f(), (*itCarniVader)->getOfVec2f(), 4) &&
				this->getSexe() != (*itCarniVader)->getSexe() && this->dataLife->listHerbi.size() < this->dataLife->limMaxHerbi)
			{
				(*itCarniVader)->duplication(this->dataLife->gestationYearCarni);

			}
		}
		if (this->babyReady()) {
			this->babyBorn();
			Carnivorous * babyCarni = new Carnivorous(this, this->imgSprite, this->dataLife, this->soundL, 0);
			babyCarni->setPosition(this->getOfVec2f());
			this->dataLife->listCarni.push_front(babyCarni);
		}

		//Valide Target Destination==================================
		if (!this->getEatLock() && (this->getEatFound() && this->herbiTarget != nullptr && !this->herbiTarget->isDead())) {
			this->calNewPath(this->herbiTarget->getOfVec2f());
			this->setEatLock(true);
		}
		if (this->getWantDuplicate() && this->carniTarget != nullptr && !this->carniTarget->isDead()) {
			this->calNewPath(this->carniTarget->getOfVec2f());
			this->setWantDuplicate(false);
			this->setEatLock(true);
		}
	}
}

void Carnivorous::calNewPath(ofVec2f d)
{
	this->x1 = this->posXY;
	this->x2 = ToolsLifeGame::getHalfPath(this->x1, d);
	//this->x3 = d;
	this->percentAnim = 0.0f;
}



void Carnivorous::draw()
{
	/*ofDrawCircle(this->x1.x, this->x1.y, 2);
	ofDrawCircle(this->x2.x, this->x2.y, 2);
	ofDrawCircle(this->x3.x, this->x3.y, 2);*/

	if (!this->dead) {
		if (this->imgSprite != nullptr) {
			ofSetColor(255, 255, 255);

			/*ofSetMatrixMode(OF_MATRIX_TEXTURE);
			ofPushMatrix();
			ofMatrix4x4 m;
			m.rotate(this->angl,0,0,1.0);
			ofMultMatrix(m);
			this->imgSprite->draw(this->posXY.x - ((this->squarHW*1.6) / 2.0f), this->posXY.y - ((this->squarHW*1.6) / 2.0f), this->squarHW*1.6, this->squarHW*1.6);
			ofPopMatrix();
			ofSetMatrixMode(OF_MATRIX_MODELVIEW);*/

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
			ofDrawRectangle(this->posXY.x - (2), this->posXY.y - (2), 4, 4);
		}
	}
}

Carnivorous::~Carnivorous()
{
	this->mother = nullptr;
	this->herbiTarget = nullptr;
	this->dataLife = nullptr;
}
