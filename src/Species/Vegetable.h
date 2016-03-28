#pragma once

#include "Species.h"

class Vegetable : public Species
{

public:
	Vegetable(ofImage * img = nullptr);
	void setPosition(ofVec2f newPos);
	void aging();
	void setAge(unsigned char age = 1);
	void update();
	void draw();
	~Vegetable();


private:
	void updateAge();
	unsigned char baseTri = 6;		//6
	unsigned char heightTri = 10;	//10

};

