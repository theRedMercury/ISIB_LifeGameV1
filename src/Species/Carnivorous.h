#pragma once

#include "Animal.h"

#include "../DataLife.h"

class DataLife;
class Carnivorous : public Animal
{

public:
	Carnivorous(Carnivorous * mama = nullptr, ofImage * img = nullptr, DataLife * data = nullptr, int numP = -1);

	void aging();
	void updateAnimation();
	void update();
	void draw();
	~Carnivorous();


private:
	void calNewPath(ofVec2f d);

	unsigned char squarHW = 12;

	ofVec2f x1;
	ofVec2f x2;
	ofVec2f x3;
	
	ofVec2f old;
	float angl = 0.0f;
	unsigned int visionAnlge = 70;	//0-360
	unsigned int visionDist = 150;
	Carnivorous * mother = nullptr;
	Animal * herbiTarget = nullptr;
	DataLife * dataLife = nullptr;
};


