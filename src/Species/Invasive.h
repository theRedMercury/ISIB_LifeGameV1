#pragma once

#include "Animal.h"
#include "../DataLife.h"

class DataLife;
class Invasive : public Animal
{
public:
	Invasive(ofImage * img = nullptr, DataLife * tool = nullptr, int numP = -1);
	void eating(unsigned char en);
	void aging();
	void updateAge();
	void updateMove();
	void update();
	void draw();
	~Invasive();

private:
	unsigned char radiusC = 2;
};

