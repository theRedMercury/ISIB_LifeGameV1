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
	~Vegetable();


private:
	unsigned char baseTri = 6;		//6
	unsigned char heightTri = 10;	//10

};

