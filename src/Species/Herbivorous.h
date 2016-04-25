#pragma once

#include "Animal.h"
#include "../DataLife.h"

class DataLife;
class Herbivorous : public Animal
{

public:
	Herbivorous(Herbivorous * mama = nullptr, ofImage * img = nullptr, DataLife * tool = nullptr, SoundLife * sound = nullptr, int numP = -1);
	void aging();
	void updateAnimation();
	void update();
	void draw();
	~Herbivorous();

private:

	void calNewPath(ofVec2f d);

	ofVec2f x1;
	ofVec2f x2;
	ofVec2f x3;
	ofVec2f x4;

	ofVec2f old;
	float angl = 0.0f;
	float visionAnlge = 60.0f;	//0-360
	float visionDist = 80.0f;
	float detectCircleSize = 125.0f;
	unsigned char radiusC = 6;

	Herbivorous * mother = nullptr;
	DataLife * dataLife = nullptr;
};