#pragma once

#include "Animal.h"
#include "../DataLife.h"

class DataLife;
class Invasive : public Animal
{
public:
	Invasive(ofImage * img = nullptr, DataLife * data = nullptr, int numP = -1);
	void aging();
	void updateAnimation();
	void update();
	void draw();
	~Invasive();

private:

	unsigned char radiusC = 2;
	ofVec2f x1;
	ofVec2f x2;
	DataLife * dataLife = nullptr;
};

