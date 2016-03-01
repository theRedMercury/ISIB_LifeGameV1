#pragma once

#include "Animal.h"
#include "../DataLife.h"

class DataLife;
class Herbivorous : public Animal
{

public:
	Herbivorous(Herbivorous * mama = nullptr, ofImage * img = nullptr, DataLife * tool = nullptr, int numP = -1);
	void eating(unsigned char en = 1);
	void aging();
	void setAge(unsigned char age = 1);
	void updateAge();
	void setNextDesti(ofVec2f n);
	float getUpdAnim();
	void updateMove();
	void update();
	void draw();
	~Herbivorous();

private:

	void calNewPath(ofVec2f d);
	unsigned char radiusC = 6;
	float getPt(float n1, float n2, float perc);

	ofVec2f x1;
	ofVec2f x2;
	ofVec2f x3;
	ofVec2f x4;

	ofVec2f old;
	float angl = 0.0f;
	unsigned int visionAnlge = 60;	//0-360
	unsigned int visionDist = 80;

	float  updAnim = 0.0;
	Herbivorous * mother = nullptr;
	DataLife * dataLife = nullptr;
};