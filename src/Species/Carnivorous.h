#pragma once

#include "Animal.h"

class Carnivorous : public Animal
{

public:
	Carnivorous(Carnivorous * mama = nullptr, ofImage * img = nullptr, ToolsLifeGame * tool = nullptr, int numP = -1);
	void eating(unsigned char en = 1);
	void aging();
	void setAge(unsigned char age = 1);
	void setNextDesti(ofVec2f n);
	void updateMove();
	void update();
	void draw();
	~Carnivorous();


private:
	float getPt(float n1, float n2, float perc);
	void updateAge();
	unsigned char squarHW = 12;

	ofVec2f x1;
	ofVec2f x2;
	ofVec2f x3;

	ofVec2f old;
	float angl = 0.0f;
	float  updAnim = 0.0;
	Carnivorous * mother = nullptr;
};


