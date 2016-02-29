#pragma once
#include "Animal.h"

class HerbivorousV2 : public Animal
{
public:
	HerbivorousV2();
	void eating(unsigned char en = 1);
	void aging();
	void setAge(unsigned char age = 1);
	void setNextDesti(ofVec2f n);
	float getUpdAnim();
	void updateMove();
	void update();
	void draw();
	~HerbivorousV2();

private :

	float getPt(float n1, float n2, float perc);

	ofVec2f x1;
	ofVec2f x2;
	ofVec2f x3;
	ofVec2f x4;

	ofVec2f old;
	float angl = 0.0f;

	float  updAnim = 0.0;
	unsigned char radiusC = 6;
};

