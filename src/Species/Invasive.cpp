#include "Invasive.h"

Invasive::Invasive(ofImage * img, DataLife * tool, int numP)
{
	this->posXY = ToolsLifeGame::getRandomPosition();
	this->setWantEat(true);

	this->shape->setHexColor(0x87872e);
	this->shape->circle(this->posXY.x, this->posXY.y, this->radiusC);
}

void Invasive::eating(unsigned char en)
{
	
}

void Invasive::aging()
{
	this->age += 1;

	if (this->age >= this->ageDead) {
		this->age = this->ageDead;
		this->dead = true;
	}
	this->updateAge();
}

void Invasive::updateAge()
{
	//this->radiusC = (((this->energy / 68.0f) + 1)* ToolsLifeGame::RadiusC) / 2.0f;
	this->shape->setColor(ofColor(46, 47, (255 - (this->age*0.7))));
	this->update();
}

void Invasive::updateMove()
{

}

void Invasive::update()
{

}

void Invasive::draw()
{
	this->shape->draw();
}

Invasive::~Invasive()
{
}
