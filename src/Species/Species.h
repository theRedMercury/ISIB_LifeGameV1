#pragma once

#include "ofMain.h"

#include "../ToolsLifeGame.h"


# define PI	3.14159265358979323846  /* pi */

class Animal;
class Vegetable;

class Species
{

public:
	Species();
	void kill();
	void setAge(unsigned char age = 1);

	ofVec2f getOfVec2f();
	unsigned char getAge();
	bool isDead();

	~Species();

	//Virtual---------------
	virtual void aging() = 0;
	virtual void setPosition(ofVec2f newPos) = 0;
	virtual void update() = 0;
	virtual void draw() = 0;


protected:

	ofVec2f posXY;
	ofPath * shape = nullptr;
	ofImage * imgSprite = nullptr;
	bool dead = false;
	unsigned char age = 0;	//0-100
};
