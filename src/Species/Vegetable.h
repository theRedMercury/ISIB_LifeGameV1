#pragma once

#include "Species.h"

class Vegetable : public Species
{

public:
	Vegetable(ofImage * img = nullptr);
	void setPosition(ofVec2f newPos);
	void aging();
	void update();
	void draw();
	bool canPropaga();
	void propagation();
	~Vegetable();


private:
	unsigned int prog = 0;
	unsigned int maxPropag = 2;
	unsigned char baseTri = 6;		//6
	unsigned char heightTri = 10;	//10

};

