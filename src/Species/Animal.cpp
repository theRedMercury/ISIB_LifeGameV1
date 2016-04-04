#include "Animal.h"

Animal::Animal()
{
	//Male or Female
	this->statut[0] = (rand() % 2 == 1);
	for (int i = 1; i < this->statut.size(); i++){
		this->statut[i] = false;
	}
	this->setWantEat(true);
	this->pregnancy = 0;
	this->energy = 55;
	this->speedMov = 1.0f;
	this->percentAnim = 0.0f;

	//cout << "Age Dead: " << (unsigned int)(this->ageDead) << endl;
}

bool Animal::babyReady()
{
	return (this->pregnancy == 0 && this->getPregnant() && !this->getSexe());
}

void Animal::babyBorn( )
{
	this->setPregnant(false);
	this->pregnancy = 0;
}

void Animal::setPosition(ofVec2f pos)
{
	this->posXY = pos;
	this->update();
}

void Animal::updateGestation(int decr)
{
	if (this->getPregnant() && !this->getSexe()) {
		this->pregnancy -= decr;
		if (this->pregnancy < 0) {
			this->pregnancy = 0;
		}
	}
}
void Animal::duplication()
{
	//Female
	if (!this->getSexe() && this->pregnancy == 0 && !this->getPregnant() && this->age > 15 && (this->age < (this->ageDead - 20))) {

		this->setPregnant(true);
		this->pregnancy = 60;
	}
}

void Animal::eating(unsigned char en)
{
	this->energy = en;
}

unsigned char Animal::getEnergy()
{
	return this->energy;
}

float Animal::getPointPercent(float n1, float n2, float perc)
{
	return n1 + ((n2 - n1) * perc);
}

//bitset===================================
bool Animal::getSexe()
{
	return this->statut[0];
}
bool Animal::getEatFound()
{
	return this->statut[1];
}
void Animal::setEatFound(bool b)
{
	this->statut[1] = b;
}
bool Animal::getWantEat()
{
	return this->statut[2];
}
void Animal::setWantEat(bool b)
{
	this->statut[2] = b;
}
bool Animal::getPregnant()
{
	return this->statut[3];
}
void Animal::setPregnant(bool b)
{
	this->statut[3] = b;
}

bool Animal::getWantDuplicate()
{
	return this->statut[4];
}
void Animal::setWantDuplicate(bool b)
{
	this->statut[4] = b;
}

Animal::~Animal()
{
	if (this->circleDetect != nullptr) {
		delete (this->circleDetect);
	}
	if (this->vision != nullptr) {
		delete (this->vision);
	}
	this->circleDetect = nullptr;
	this->vision = nullptr;
	this->tools = nullptr;
}
