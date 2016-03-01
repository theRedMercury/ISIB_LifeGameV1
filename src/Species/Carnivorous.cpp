#include "Carnivorous.h"


Carnivorous::Carnivorous(Carnivorous * mama, ofImage * img, DataLife * tool, int numP)
{
	this->dataLife = tool;
	this->numPack = numP;
	if (mama != nullptr) {
		this->mother = mama;
		this->x1 = this->mother->getOfVec2f();
		this->x2 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 10 + this->mother->getAge() / 10.0f);
		this->x3 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 8 + this->mother->getAge() / 10.0f);
	}
	else {
		
		
			this->x1 = ToolsLifeGame::getRandomPosition();
		
		this->x2 = ToolsLifeGame::getRandomPosition(this->x1, 250);
		this->x3 = ToolsLifeGame::getRandomPosition(this->x2, 250);
	}

	if (img != nullptr) {
		this->imgSprite = img;
	}
	else {
		this->shape->setHexColor(0x872f30);
		this->shape->rectangle(this->posXY.x - (this->squarHW / 2.0f), this->posXY.y - (this->squarHW / 2.0f), this->squarHW, this->squarHW);
		
	}

	this->old.x = this->posXY.x;
	this->old.y = this->posXY.y;
	this->circleDetect = new ofPath();
	this->circleDetect->setColor(ofColor(216, 46, 46, 50));
	this->circleDetect->circle(this->posXY.x, this->posXY.y, 75);
	this->vision = new ofPath();
	this->vision->setColor(ofColor(216, 200, 200, 50));
	this->vision->arc(this->posXY.x, this->posXY.y, 75, 75, 90, 180);

	/*this->shape->setHexColor(0x872f30);
	this->shape->rectangle(this->posXY.x - (this->squarHW / 2), this->posXY.y - (this->squarHW / 2), this->squarHW, this->squarHW);
	this->x1 = this->mother->getOfVec2f();
	this->x2 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 10 + this->mother->getAge() / 10);
	this->x3 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 8 + this->mother->getAge() / 10);*/
}

void Carnivorous::eating(unsigned char en)
{

}

void Carnivorous::aging()
{
	this->age += 1;
	if (this->age >= this->ageDead) {
		this->age = this->ageDead;
		this->dead = true;
	}
	this->updateAge();
}

void Carnivorous::setAge(unsigned char age)
{
	this->age = age;
	this->updateAge();
}

void Carnivorous::setNextDesti(ofVec2f n)
{
	this->nextDesti = n;
}

void Carnivorous::updateAge()
{
	this->squarHW = (((this->age / 32.0f) + 1)* ToolsLifeGame::SquarHW) / 2.0f;
	this->shape->setColor(ofColor((255 - (this->age*1.0)), 47, 48));
	this->update();
}


void Carnivorous::updateMove()
{
	if (this->mother != nullptr && this->age <  15) {

		this->updAnim += 0.025*this->speedMov;

		float xa = getPt(this->x1.x, this->x2.x, this->updAnim);
		float ya = getPt(this->x1.y, this->x2.y, this->updAnim);
		float xb = getPt(this->x2.x, this->x3.x, this->updAnim);
		float yb = getPt(this->x2.y, this->x3.y, this->updAnim);

		// The Black Dot
		this->posXY.x = getPt(xa, xb, this->updAnim);
		this->posXY.y = getPt(ya, yb, this->updAnim);

		this->shape->clear();
		this->shape->rectangle(this->posXY.x - (this->squarHW / 2.0f), this->posXY.y - (this->squarHW / 2.0f), this->squarHW, this->squarHW);


		if (this->updAnim >= 1.0) {
			this->x1 = this->posXY;
			this->x2 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 10 + this->mother->getAge() / 8.0f);
			this->x3 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 8 + this->mother->getAge() / 10.0f);

			this->updAnim = 0;
		}
	}
	else {
		
		float dist = (1.0 / (abs(sqrt(pow(this->x2.x - this->x3.x, 2) + pow(this->x2.x - this->x3.x, 2)))+0.001f)) / 2.0f;
		if (dist > 0.06) {
			this->updAnim += 0.05*this->speedMov;
		}
		else {
			this->updAnim += dist*this->speedMov;
		}

		float xa = getPt(this->x1.x, this->x2.x, this->updAnim);
		float ya = getPt(this->x1.y, this->x2.y, this->updAnim);
		float xb = getPt(this->x2.x, this->x3.x, this->updAnim);
		float yb = getPt(this->x2.y, this->x3.y, this->updAnim);

		
		this->old.x = this->posXY.x;
		this->old.y = this->posXY.y;

		this->posXY.x = getPt(xa, xb, this->updAnim);
		this->posXY.y = getPt(ya, yb, this->updAnim);

		this->angl = atan2f(this->posXY.y - this->old.y, this->posXY.x - this->old.x)* (180.0f / PI);


		
		this->vision->clear();
		this->vision->arc(this->posXY.x, this->posXY.y, this->visionDist, this->visionDist, this->angl - (this->visionAnlge / 2), this->angl + (this->visionAnlge / 2));
		this->circleDetect->clear();
		this->circleDetect->circle(this->posXY.x, this->posXY.y, 75);

		this->shape->clear();
		this->shape->rectangle(this->posXY.x - (this->squarHW / 2.0f), this->posXY.y - (this->squarHW / 2.0f), this->squarHW, this->squarHW);
		
		if (this->updAnim >= 1.0) {
			this->x1 = this->posXY;
			this->x2 = ToolsLifeGame::getRandomPosition(this->x1, 45);
			//this->x3 = ToolsLifeGame::getRandomPosition(this->x2, 150);
			
				
			
				this->x3 = ToolsLifeGame::getRandomPosition(this->x2, 120);
			
			this->updAnim = 0;
		}
	}
}

void Carnivorous::update()
{
	this->shape->clear();
	this->shape->rectangle(this->posXY.x - (this->squarHW / 2.0f), this->posXY.y - (this->squarHW / 2.0f), this->squarHW, this->squarHW);
}

float Carnivorous::getPt(float n1, float n2, float perc)
{
	return n1 + ((n2 - n1) * perc);
}

void Carnivorous::draw()
{
	/*ofDrawCircle(this->x1.x, this->x1.y, 2);
	ofDrawCircle(this->x2.x, this->x2.y, 2);
	ofDrawCircle(this->x3.x, this->x3.y, 2);*/
	
	if (!this->dead) {
		//this->shape->draw();
		if (this->imgSprite != nullptr) {
			ofSetColor(255, 255, 255);
			this->imgSprite->draw(this->posXY.x - ((this->squarHW*1.6) / 2.0f), this->posXY.y - ((this->squarHW*1.6)/2.0f), this->squarHW*1.6, this->squarHW*1.6);
		}
		else {
			this->circleDetect->draw();
			this->vision->draw();
			this->shape->draw();
		}

		if (this->pregnancy > 1 && !this->sexe && this->pregnant) {
			ofSetColor(255, 255, 255);
			ofDrawRectangle(this->posXY.x - (2), this->posXY.y - (2), 4, 4);
		}
	}
}

Carnivorous::~Carnivorous()
{
	this->dead = true;

}
