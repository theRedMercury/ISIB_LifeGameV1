#include "Animal.h"

Animal::Animal()
{
	//Male or Female
	this->sexe = (rand() % 2 == 1);
	this->pregnant = false;
	this->pregnancy = 0;
	this->energy = 55;
	this->speedMov =1.0f;
	this->ageDead = (unsigned char)(100+((rand()%21)-10));
	this->nextDesti.x = -1;
	//fprintf(stderr, "Age : %i \n", this->ageDead);
	//cout << "Age Dead: " << (this->ageDead) << endl;
}

bool Animal::getSexe()
{
	return this->sexe;
}

bool Animal::babyReady()
{
	return (this->pregnancy == 0 && this->pregnant && !this->sexe);
}

void Animal::babyBorn( )
{
	this->pregnant = false;
	this->pregnancy = 0;
}

void Animal::setPosition(ofVec2f pos)
{
	this->posXY = pos;
	this->update();
}

void Animal::updateGestation(int decr)
{
	if (this->pregnant && !this->sexe) {
		this->pregnancy -= decr;
		if (this->pregnancy < 0) {
			this->pregnancy = 0;
		}
	}
}
void Animal::duplication()
{
	//Female
	if (!this->sexe && this->pregnancy == 0 && !this->pregnant && this->age > 15 && (this->age < (this->ageDead - 20))) {

		this->pregnant = true;
		this->pregnancy = 255;
	}
}

void Animal::setEnergy(unsigned char en)
{
	this->energy = en;
}

unsigned char Animal::getEnergy()
{
	return this->energy;
}

bool Animal::getEatFound() {
	return this->statut[0];
}
void Animal::setEatFound(bool b)
{
	this->statut[0] = b;
}

Animal::~Animal()
{

}
