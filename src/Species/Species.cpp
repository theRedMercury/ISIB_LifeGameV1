#include "Species.h"

Species::Species()
{
	this->posXY = ofVec2f(0, 0);
	this->shape = new ofPath();
}

void Species::setAge(unsigned char age)
{
	this->age = age;
}

ofVec2f Species::getOfVec2f()
{
	return this->posXY;
}

unsigned char Species::getAge()
{
	return this->age;
}

void Species::kill()
{
	this->dead = true;
}

bool Species::isDead()
{
	return this->dead;
}

Species::~Species()
{
	if (this->shape != nullptr) {
		delete this->shape;
		this->shape = nullptr;
	}
	if (this->imgSprite != nullptr) {
		this->imgSprite = nullptr;
	}
}
