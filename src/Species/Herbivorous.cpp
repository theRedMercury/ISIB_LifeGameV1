#include "Herbivorous.h"


Herbivorous::Herbivorous(Herbivorous * mama, ofImage * img, ToolsLifeGame * tool, int numP)
{
	this->tools = tool;
	this->numPack = numP;

	if (mama != nullptr) {
		this->mother = mama;
		this->x1 = this->mother->getOfVec2f();
		this->x2 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 10 + this->mother->getAge() / 10.0f);
		this->x3 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 8 + this->mother->getAge() / 10.0f);
	}
	else {
		if (this->numPack != -1) {
			this->x1 = ToolsLifeGame::getRandomPosition(this->tools->listHerPack.at(this->numPack));
		}
		else {
			this->x1 = ToolsLifeGame::getRandomPosition();
		}
		this->x2 = ToolsLifeGame::getRandomPosition(this->x1, 250);
		this->x3 = ToolsLifeGame::getRandomPosition(this->x2, 250);
		this->x4 = ToolsLifeGame::getRandomPosition(this->tools->listHerPack.at(0), 250);
	}

	if (img != nullptr) {
		this->imgSprite = img;
	}
	else {
		this->shape->setHexColor(0x2e2f87);
		this->shape->circle(this->posXY.x, this->posXY.y, this->radiusC);
	}	
}

void Herbivorous::eating(unsigned char en)
{
	this->energy += en;
}

void Herbivorous::aging()
{
	this->age += 1;
	if (this->age >= this->ageDead) {
		this->age = this->ageDead;
		this->dead = true;
	}
	this->updateAge();
}

void Herbivorous::setAge(unsigned char age)
{
	this->age = age;
	this->updateAge();
}

float Herbivorous::getUpdAnim()
{
	return this->updAnim;
}

void Herbivorous::updateAge()
{
	this->radiusC = (((this->energy / 68.0f) + 1)* ToolsLifeGame::RadiusC) / 2.0f;
	this->shape->setColor(ofColor( 46,47,(255 - (this->age*0.7))));
	this->update();
}

float Herbivorous::getPt(float n1, float n2, float perc)
{
	return n1 + ((n2 - n1) * perc);
}

void Herbivorous::setNextDesti(ofVec2f n)
{
	this->nextDesti = n;
}

void Herbivorous::updateMove()
{
	if (this->mother != nullptr && this->age <  15  ) {

		this->updAnim += 0.025*this->speedMov;

		int xa = getPt(this->x1.x, this->x2.x, this->updAnim);
		int ya = getPt(this->x1.y, this->x2.y, this->updAnim);
		int xb = getPt(this->x2.x, this->x3.x, this->updAnim);
		int yb = getPt(this->x2.y, this->x3.y, this->updAnim);

		// The Black Dot
		this->posXY.x = getPt(xa, xb, this->updAnim);
		this->posXY.y = getPt(ya, yb, this->updAnim);

		this->shape->clear();
		this->shape->circle(this->posXY.x, this->posXY.y, this->radiusC);


		if (this->updAnim >= 1.0) {
			this->x1 = this->posXY;
			this->x2 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 10+this->mother->getAge()/8.0f);
			this->x3 = ToolsLifeGame::getRandomPosition(this->mother->getOfVec2f(), 8 + this->mother->getAge() / 10.0f);
			this->x4 = ToolsLifeGame::getRandomPosition(this->x3,50);
			this->updAnim = 0;
		}
	}
	else {
		float dist = (1.0 / (abs(sqrt(pow(this->x1.x - this->x4.x, 2) + pow(this->x1.x - this->x4.x, 2)))+0.001f)) / 2.0f;
		if (dist > 0.003) {
			this->updAnim += 0.002*this->speedMov;
		}
		else {
			this->updAnim += dist*this->speedMov;
		}

		int xa = getPt(this->x1.x, this->x2.x, this->updAnim);
		int ya = getPt(this->x1.y, this->x2.y, this->updAnim);
		int xb = getPt(this->x2.x, this->x3.x, this->updAnim);
		int yb = getPt(this->x2.y, this->x3.y, this->updAnim);

		int xaa = getPt(this->x2.x, this->x3.x, this->updAnim);
		int yaa = getPt(this->x2.y, this->x3.y, this->updAnim);
		int xbb = getPt(this->x3.x, this->x4.x, this->updAnim);
		int ybb = getPt(this->x3.y, this->x4.y, this->updAnim);

		// The Black Dot
		int xa1 = getPt(xa, xb, this->updAnim);
		int ya1 = getPt(ya, yb, this->updAnim);
		int xa2 = getPt(xaa, xbb, this->updAnim);
		int ya2 = getPt(yaa, ybb, this->updAnim);

		this->posXY.x = getPt(xa1, xa2, this->updAnim);
		this->posXY.y = getPt(ya1, ya2, this->updAnim);
		this->shape->clear();
		this->shape->circle(this->posXY.x, this->posXY.y, this->radiusC);


		if (this->updAnim >= 1.0) {
			this->x1 = this->posXY;
			this->x2 = ToolsLifeGame::getRandomPosition(this->x1, 45);
			//this->x3 = ToolsLifeGame::getRandomPosition(this->x2, 55);

			if (this->numPack != -1) {
				this->x3 = ToolsLifeGame::getRandomPosition(this->tools->listHerPack.at(this->numPack),50);
			}
			else {
				this->x3 = ToolsLifeGame::getRandomPosition(this->x2, 120);
			}

			if (this->nextDesti.x != -1) {
				this->x4 = ToolsLifeGame::getRandomPosition(this->nextDesti, 150);
			}
			else {
				this->x4 = ToolsLifeGame::getRandomPosition(this->tools->listHerPack.at(0), 150);
			}
			this->updAnim = 0;
		}
	}
}
void Herbivorous::update()
{
	this->shape->clear();
	this->shape->circle(this->posXY.x, this->posXY.y, this->radiusC);
}

void Herbivorous::draw()
{
	/*ofDrawCircle(this->x1.x, this->x1.y, 2);
	ofDrawCircle(this->x2.x, this->x2.y, 2);
	ofDrawCircle(this->x3.x, this->x3.y, 2);
	ofDrawCircle(this->x4.x, this->x4.y, 2);*/
	
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
			this->shape->draw();
		}

		if (this->pregnancy > 1 && !this->sexe && this->pregnant) {
			ofSetColor(255, 255, 255);
			ofDrawCircle(this->posXY, 2);
		}
		
	}
}

Herbivorous::~Herbivorous()
{
	this->dead = true;
	/*if (this->mother != nullptr) {
		fprintf(stderr, "KILL MAMA...\n");
		delete this->mother;
		this->mother = nullptr;
	}*/
}
