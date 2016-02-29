#include "HerbivorousV2.h"



HerbivorousV2::HerbivorousV2()
{
	this->shape->setHexColor(0x2e2f87);
	this->x1 = ToolsLifeGame::getRandomPosition();
	this->x2 = ToolsLifeGame::getRandomPosition(this->x1, 250);
	this->x3 = ToolsLifeGame::getRandomPosition(this->x2, 250);
	this->x4 = ToolsLifeGame::getRandomPosition(this->x3, 250);


	this->posXY.x = 150;
	this->posXY.y = 150;
	this->old.x = this->posXY.x;
	this->old.y = this->posXY.y;
	this->circleDetect = new ofPath();
	this->circleDetect->setColor(ofColor(46, 46, 216, 50));
	this->vision = new ofPath();
	this->vision->setColor(ofColor(200, 200, 216, 50));
	this->vision->arc(this->posXY.x, this->posXY.y, 75, 75, 90, 180);

	this->circleDetect->circle(this->posXY.x, this->posXY.y, 75);
	this->shape->circle(this->posXY.x, this->posXY.y, this->radiusC);
}

void HerbivorousV2::eating(unsigned char en)
{}
void HerbivorousV2::aging()
{}
void HerbivorousV2::setAge(unsigned char age)
{}
void HerbivorousV2::setNextDesti(ofVec2f n)
{}
float HerbivorousV2::getUpdAnim()
{
	return 0.0f;
}
float HerbivorousV2::getPt(float n1, float n2, float perc)
{
	return n1 + ((n2 - n1) * perc);
}

void HerbivorousV2::updateMove()
{
	float dist = (1.0 / (abs(sqrt(pow(this->x1.x - this->x4.x, 2) + pow(this->x1.x - this->x4.x, 2))) + 0.001f)) / 2.0f;
	if (dist > 0.003) {
		this->updAnim += 0.002*this->speedMov;
	}
	else {
		this->updAnim += dist*this->speedMov;
	}

	float xa = getPt(this->x1.x, this->x2.x, this->updAnim);
	float ya = getPt(this->x1.y, this->x2.y, this->updAnim);
	float xb = getPt(this->x2.x, this->x3.x, this->updAnim);
	float yb = getPt(this->x2.y, this->x3.y, this->updAnim);

	float xaa = getPt(this->x2.x, this->x3.x, this->updAnim);
	float yaa = getPt(this->x2.y, this->x3.y, this->updAnim);
	float xbb = getPt(this->x3.x, this->x4.x, this->updAnim);
	float ybb = getPt(this->x3.y, this->x4.y, this->updAnim);

	// The Black Dot
	float xa1 = getPt(xa, xb, this->updAnim);
	float ya1 = getPt(ya, yb, this->updAnim);
	float xa2 = getPt(xaa, xbb, this->updAnim);
	float ya2 = getPt(yaa, ybb, this->updAnim);

	this->old.x = this->posXY.x;
	this->old.y = this->posXY.y;

	this->posXY.x = getPt(xa1, xa2, this->updAnim);
	this->posXY.y = getPt(ya1, ya2, this->updAnim);
	angl = atan2f(this->posXY.y - this->old.y, this->posXY.x - this->old.x)* (180.0f / PI);
	
	
	this->shape->clear();
	this->shape->circle(this->posXY.x, this->posXY.y, this->radiusC);
	this->vision->clear();
	this->vision->arc(this->posXY.x, this->posXY.y, 75, 75, angl-30, angl+30);
	this->circleDetect->clear();
	this->circleDetect->circle(this->posXY.x, this->posXY.y, 75);


	if (this->updAnim >= 1.0) {
		this->x1 = this->posXY;
		this->x2 = ToolsLifeGame::getRandomPosition(this->x1, 45);
		this->x3 = ToolsLifeGame::getRandomPosition(this->x2, 120);
		this->x4 = ToolsLifeGame::getRandomPosition(this->x3, 150);
		this->updAnim = 0;
	}
}

void HerbivorousV2::update()
{

}
void HerbivorousV2::draw()
{
	this->shape->draw();
	
	this->circleDetect->draw();
	this->vision->draw();
}

HerbivorousV2::~HerbivorousV2()
{
}
