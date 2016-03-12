#include "Invasive.h"

Invasive::Invasive(ofImage * img, DataLife * tool, int numP)
{
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
