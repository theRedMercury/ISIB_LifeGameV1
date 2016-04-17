#include "Invasive.h"

Invasive::Invasive(ofImage * img, DataLife * data, int numP)
{
	this->dataLife = data;
	this->ageDead = (unsigned char)(100 + ((rand() % 21) - 10));

	
	if (rand() % 2 == 1) {
		this->posXY = ToolsLifeGame::getRandomPosition(ofVec2f(ofGetWindowWidth() / 1.5f, ofGetWindowHeight() / 2.0f));
	}
	else {
		this->posXY = ToolsLifeGame::getRandomPosition(ofVec2f(ofGetWindowWidth() / 2.5f, ofGetWindowHeight() / 2.0f));
	}

	this->x1 = this->posXY;
	this->x2 = ToolsLifeGame::getRandomPosition(this->x1, 200);
	
	this->shape->setHexColor(0x87872e);
	this->shape->circle(this->posXY.x, this->posXY.y, this->radiusC);
}


void Invasive::aging()
{
	this->age += 1;

	if (this->age >= this->ageDead) {
		this->age = this->ageDead;
		this->dead = true;
	}
	/*	this->radiusC = (((this->energy / 68.0f) + 1)* ToolsLifeGame::RadiusC) / 2.0f;
	this->shape->setColor(ofColor(46, 47, (255 - (this->age*0.7))));*/
}

void Invasive::updateAnimation()
{
	float dist = (1.0 / (abs(sqrt(pow(this->x1.x - this->x2.x, 2) + pow(this->x1.x - this->x2.x, 2))) + 0.001f)) / 1.2f;
	if (dist > 0.081) {
		this->percentAnim += 0.08*this->speedMov;
	}
	else {
		this->percentAnim += dist*this->speedMov;
	}

	this->posXY.x = getPointPercent(this->x1.x, this->x2.x, this->percentAnim);
	this->posXY.y = getPointPercent(this->x1.y, this->x2.y, this->percentAnim);

	if (this->percentAnim >= 1.0) {
		this->x1 = this->posXY;
		this->x2 = ToolsLifeGame::getRandomPosition(this->x1, 75);
		this->percentAnim = 0;
	}
	this->shape->clear();
	this->shape->circle(this->posXY.x, this->posXY.y, this->radiusC);
}

void Invasive::update()
{
	//Eat Tree===================================
	this->dataLife->lockListTrees.lock();
	for (list<Vegetable*>::iterator itTree = this->dataLife->listTrees.begin(); itTree != this->dataLife->listTrees.end(); itTree++)
	{
		if (ToolsLifeGame::checkCollision(this->getOfVec2f(), (*itTree)->getOfVec2f(), 4)) {
			this->eating((*itTree)->getAge() / 10);
			(*itTree)->kill();
		}
	}
	this->dataLife->lockListTrees.unlock();
}

void Invasive::draw()
{
	this->shape->draw();
}

Invasive::~Invasive()
{
	this->dataLife = nullptr;
}
