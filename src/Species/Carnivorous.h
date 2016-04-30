#pragma once

#include "Animal.h"

#include "../DataLife.h"

class DataLife;
class Carnivorous : public Animal
{

public:
	Carnivorous(Carnivorous * mama = nullptr, ofImage * img = nullptr, DataLife * data = nullptr, SoundLife * sound = nullptr, int numP = -1);

	void aging();
	void updateAnimation();
	void update();
	void draw();

	~Carnivorous();


private:
	void calNewPath(ofVec2f d);

	ofVec2f x1;
	ofVec2f x2;
	ofVec2f x3;
	
	ofVec2f old;
	float angl = 0.0f;
	float visionAnlge = 70.0f;	//0-360
	float visionDist = 150.0f;
	float detectCircleSize = 125.0f;
	bool showVision = false;
	unsigned char squarHW = 12;

	Carnivorous * mother = nullptr;
	Animal * herbiTarget = nullptr;
	Animal * carniTarget = nullptr;
	DataLife * dataLife = nullptr;
};


