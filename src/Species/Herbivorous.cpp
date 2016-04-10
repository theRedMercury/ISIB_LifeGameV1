#include "Herbivorous.h"

Herbivorous::Herbivorous(Herbivorous * mama, ofImage * img, DataLife * tool, int numP)
{
	this->dataLife = tool;
	this->ageDead = (unsigned char)(90 + ((rand() % 21) - 10));

	this->setEatFound(false);
	if (mama != nullptr) {
		this->mother = mama;
		this->x1 = this->mother->getOfVec2f();
		this->x2 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 10 + this->mother->getAge() / 10.0f);
		this->x3 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 8 + this->mother->getAge() / 10.0f);
		this->x4 = ToolsLifeGame::getRandomPosition(this->x3, 150);
	}
	else {
		this->x1 = ToolsLifeGame::getRandomPosition();
		this->x2 = ToolsLifeGame::getRandomPosition(this->x1, 250);
		this->x3 = ToolsLifeGame::getRandomPosition(this->x2, 250);
		this->x4 = ToolsLifeGame::getRandomPosition(this->x3, 150);
	}

	if (img != nullptr) {
		this->imgSprite = img;
	}
	else {
		this->shape->setHexColor(0x2e2f87);
		this->shape->circle(this->posXY.x, this->posXY.y, this->radiusC);
	}	


	this->old.x = this->posXY.x;
	this->old.y = this->posXY.y;
	this->circleDetect = new ofPath();
	this->circleDetect->setColor(ofColor(46, 46, 216, 50));
	this->circleDetect->circle(this->posXY.x, this->posXY.y, 75);
	this->vision = new ofPath();
	this->vision->setColor(ofColor(200, 200, 216, 50));
	this->vision->arc(this->posXY.x, this->posXY.y, 75, 75, 90, 180);
}



void Herbivorous::aging()
{
	this->age += 1;
	this->visionDist += 1;
	
	if (this->age >= this->ageDead) {
		this->age = this->ageDead;
		this->visionDist -= 1;

		//this->dead = true;
	}
}



float Herbivorous::getUpdAnim()
{
	return this->percentAnim;
}


void Herbivorous::updateAnimation()
{
	//Follow Mother----------------------------------
	if (this->mother != nullptr && this->age <  15  ) {

		this->percentAnim += 0.025*this->speedMov;
		this->posXY.x = getPointPercent(getPointPercent(this->x1.x, this->x2.x, this->percentAnim), getPointPercent(this->x2.x, this->x3.x, this->percentAnim), this->percentAnim);
		this->posXY.y = getPointPercent(getPointPercent(this->x1.y, this->x2.y, this->percentAnim), getPointPercent(this->x2.y, this->x3.y, this->percentAnim), this->percentAnim);

		if (this->percentAnim >= 1.0) {
			this->x1 = this->posXY;
			this->x2 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 10+this->mother->getAge()/8.0f);
			this->x3 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 8 + this->mother->getAge() / 10.0f);
			this->x4 = ToolsLifeGame::getRandomPosition(this->x3,50);
			this->setEatFound(false);
			this->percentAnim = 0;
		}
	}
	else {
		float dist = (1.0 / (abs(sqrt(pow(this->x1.x - this->x4.x, 2) + pow(this->x1.x - this->x4.x, 2))) + 0.001f)) / 2.0f;
		if (dist > 0.003) {
			this->percentAnim += 0.002*this->speedMov;
		}
		/*if (dist < 0.000001) {
			this->percentAnim += 0.00008*this->speedMov;
		}*/
		else {
			this->percentAnim += dist*this->speedMov;
		}

		float xa1 = getPointPercent(getPointPercent(this->x1.x, this->x2.x, this->percentAnim), getPointPercent(this->x2.x, this->x3.x, this->percentAnim), this->percentAnim);
		float ya1 = getPointPercent(getPointPercent(this->x1.y, this->x2.y, this->percentAnim), getPointPercent(this->x2.y, this->x3.y, this->percentAnim), this->percentAnim);
		float xa2 = getPointPercent(getPointPercent(this->x2.x, this->x3.x, this->percentAnim), getPointPercent(this->x3.x, this->x4.x, this->percentAnim), this->percentAnim);
		float ya2 = getPointPercent(getPointPercent(this->x2.y, this->x3.y, this->percentAnim), getPointPercent(this->x3.y, this->x4.y, this->percentAnim), this->percentAnim);

		this->old.x = this->posXY.x;
		this->old.y = this->posXY.y;

		this->posXY.x = getPointPercent(xa1, xa2, this->percentAnim);
		this->posXY.y = getPointPercent(ya1, ya2, this->percentAnim);
		this->angl = atan2f(this->posXY.y - this->old.y, this->posXY.x - this->old.x)* (180.0f / PI);

		this->vision->clear();
		this->vision->arc(this->posXY.x, this->posXY.y, this->visionDist, this->visionDist, this->angl - (this->visionAnlge / 2), this->angl + (this->visionAnlge/2));
		this->circleDetect->clear();
		this->circleDetect->circle(this->posXY.x, this->posXY.y, 75);

		if (this->percentAnim >= 1.0) {
			this->x1 = this->posXY;
			this->x2 = ToolsLifeGame::getRandomPosition(this->x1, 45);
			this->x3 = ToolsLifeGame::getRandomPosition(this->x2, 120);
			this->x4 = ToolsLifeGame::getRandomPosition(this->x3, 150);
			this->setEatFound(false);
			this->percentAnim = 0;
		}
	}
	this->shape->clear();
	this->shape->circle(this->posXY.x, this->posXY.y, this->radiusC);

}

void Herbivorous::update()
{
	bool eatFound = false;
	float eatDist = this->visionDist + 10.0f;
	ofVec2f dest;

	if (this->energy > 50) {
		this->energy -= 5;
	}
	this->setWantEat(this->energy < 75);

	//TREE MANAGE==============================================
	this->dataLife->lockListTrees.lock();
	for (list<Vegetable*>::iterator itTree = this->dataLife->listTrees.begin(); itTree != this->dataLife->listTrees.end(); )
	{
	
		if (ToolsLifeGame::getDistance(this->posXY, (*itTree)->getOfVec2f()) < eatDist && (*itTree)->getAge() > 5 && !this->getEatFound() && this->getWantEat() &&
			ToolsLifeGame::arCCollision(this->posXY, this->angl, this->visionAnlge, this->visionDist, (*itTree)->getOfVec2f())) {
			eatFound = true;
			eatDist = ToolsLifeGame::getDistance(this->posXY, (*itTree)->getOfVec2f());
			dest = (*itTree)->getOfVec2f();
		}

		//Eat Tree
		if (this->getEnergy()<220 && (*itTree)->getAge() > 15 && ToolsLifeGame::checkCollision(this->getOfVec2f(), (*itTree)->getOfVec2f(), 8)) {
			this->eating((*itTree)->getAge() / 10);
			delete * itTree;
			(*itTree) = nullptr;
			itTree = this->dataLife->listTrees.erase(itTree);
		}
		else {
			itTree++;
		}
		
	}
	this->dataLife->lockListTrees.unlock();
	
	//HERBI MANAGE==============================================
	for (list<Herbivorous*>::iterator itHerbiVader = this->dataLife->listHerbi.begin(); itHerbiVader != this->dataLife->listHerbi.end(); itHerbiVader++)
	{
		if (this != (*itHerbiVader) &&
			ToolsLifeGame::checkCollision(this->getOfVec2f(), (*itHerbiVader)->getOfVec2f(), 4) &&
			this->getSexe() != (*itHerbiVader)->getSexe() && this->dataLife->listHerbi.size() < this->dataLife->limitCarni)
		{
			(*itHerbiVader)->duplication();
		}
	}
	if (this->babyReady()) {
		this->babyBorn();
		Herbivorous * babyHerbi = new Herbivorous(this, this->imgSprite, this->dataLife);
		babyHerbi->setPosition(this->getOfVec2f());
		babyHerbi->setAge(1);
		//fprintf(stderr, "Born...\n");
		this->dataLife->listHerbi.push_front(babyHerbi);
	}

	//===========================================
	if (eatFound && !this->getEatFound()) {
		this->calNewPath(dest);
		this->setEatFound(true);
	}
}


void Herbivorous::calNewPath(ofVec2f d)
{
	this->x1 = this->posXY;
	this->x2 = ToolsLifeGame::getHalfPath(this->x1, d);
	this->x3 = ToolsLifeGame::getHalfPath(this->x2, d);
	this->x4 = d;
	this->percentAnim = 0;
}

void Herbivorous::draw()
{
	ofDrawCircle(this->x1.x, this->x1.y, 2);
	ofDrawCircle(this->x2.x, this->x2.y, 2);
	ofDrawCircle(this->x3.x, this->x3.y, 2);
	ofDrawCircle(this->x4.x, this->x4.y, 2);
	
	if (!this->dead) {
		
		//this->shape->draw();
		if (this->imgSprite != nullptr) {
			if (this->age > 50) {
				ofSetColor(255 - (this->age/2), 255 - (this->age / 2), 255 - (this->age / 2));
			}
			else {
				ofSetColor(255, 255, 255);
			}
			this->imgSprite->draw(this->posXY.x - ((this->radiusC*3) / 2.0f), (this->posXY.y - (this->radiusC*3)/2.0f), this->radiusC*3, this->radiusC*3);
		}

		else {
			this->circleDetect->draw();
			this->vision->draw();
			this->shape->draw();
		}
		if (this->pregnancy > 1 && !this->getSexe() && this->getPregnant()) {
			ofSetColor(255, 255, 255);
			ofDrawCircle(this->posXY, 2);
		}
		
	}
}

Herbivorous::~Herbivorous()
{
	this->dead = true;
	this->mother = nullptr;
	this->dataLife = nullptr;
}
