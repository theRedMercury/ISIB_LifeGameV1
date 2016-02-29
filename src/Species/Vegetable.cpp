#include "Vegetable.h"


Vegetable::Vegetable(ofImage * img)
{
	if (img != nullptr) {
		this->imgSprite = img;
	}
	else {
		this->shape->setHexColor(0x2E8730);
		this->shape->triangle(this->posXY.x - (this->baseTri / 2.0f), this->posXY.y + (this->baseTri / 2.0f), this->posXY.x, this->posXY.y - (this->heightTri / 2.0f), this->posXY.x + (this->baseTri / 2.0f), this->posXY.y + (this->baseTri / 2.0f));
	}
	//this->shape->setHexColor(0x2E8730);
	//this->shape->triangle(this->posXY.x - (this->baseTri / 2), this->posXY.y + (this->baseTri / 2), this->posXY.x, this->posXY.y - (this->heightTri / 2), this->posXY.x + (this->baseTri / 2), this->posXY.y + (this->baseTri / 2));
}
void Vegetable::setPosition(float x, float y)
{	
	this->posXY.x = x;
	this->posXY.y = y;

	this->update();
}

void Vegetable::setPosition(ofVec2f newPos)
{
	this->posXY.x = newPos.x;
	this->posXY.y = newPos.y;
	this->update();
}

void Vegetable::aging()
{
	this->age += 1;
	if (this->age >= 100) {
		this->age = 100;
	}
	this->updateAge();
}

void Vegetable::setAge(unsigned char age)
{
	this->age = age;
	this->updateAge();
}

void Vegetable::updateAge()
{
	this->baseTri = (((this->age / 32.0f) + 1)* ToolsLifeGame::BaseTri) / 2.0f;
	this->heightTri = (((this->age / 32.0f) + 1)* ToolsLifeGame::HeightTri) / 2.0f;
	this->shape->setColor(ofColor(46, (255 - (this->age*1.1)), 48));
	this->update();
}

void Vegetable::update()
{
	this->shape->clear();
	
	this->shape->triangle(this->posXY.x - this->baseTri, this->posXY.y + this->baseTri, this->posXY.x, this->posXY.y - this->heightTri, this->posXY.x + this->baseTri, this->posXY.y + this->baseTri);
}

void Vegetable::draw()
{
	if (!this->dead) {
		//this->shape->draw();
		if (this->imgSprite != nullptr) {
			ofSetColor(255, 255, 255);
			this->imgSprite->draw(this->posXY.x-((this->heightTri*1.6)/2.0f),this->posXY.y - ((this->heightTri*2.5)/2.0f), this->heightTri*1.6, this->heightTri*2.5);
		}
		else {
			this->shape->draw();
		}
	}
	
}

Vegetable::~Vegetable()
{
	this->dead = true;	
}
