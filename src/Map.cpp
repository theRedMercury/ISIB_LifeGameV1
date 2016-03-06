#include "Map.h"

Map::Map(DataLife * dataL)
{
	this->dataLife = dataL;

	this->mapImg = new ofImage();
	if (this->mapImg->loadImage("backGround.jpg")) {
		this->mapImg->allocate(2400, 1600, OF_IMAGE_COLOR);
		this->mapImg->setCompression(ofTexCompression::OF_COMPRESS_ARB);
	}
	else {
		delete (this->mapImg);
		this->mapImg = nullptr;
	}

	this->vegetalImage = new ofImage();
	if (this->vegetalImage->loadImage("tree.png")) {
		this->vegetalImage->allocate(112, 127, OF_IMAGE_COLOR_ALPHA);
	}
	else {
		delete (this->vegetalImage);
		this->vegetalImage = nullptr;
	}

	this->posMountain = ToolsLifeGame::getRandomPosition(ofVec2f((ofGetWidth() - 150), 100), 75);
	this->posDessert = ToolsLifeGame::getRandomPosition(ofVec2f(100, 100), 75);
	this->posForest = ToolsLifeGame::getRandomPosition(ofVec2f((ofGetWidth() - 350), (ofGetHeight() - 150)), 75);

	this->waterImg = new ofImage("water.jpg");
	this->waterImg->allocate(1920, 1440, OF_IMAGE_COLOR);
	this->waterImg->setCompression(ofTexCompression::OF_COMPRESS_ARB);

	for (int i = 0; i < 15; i++) {
		Vegetable * tree = new Vegetable(this->vegetalImage);
		tree->setPosition(ToolsLifeGame::getRandomPosition(this->posForest, 250));
		tree->setAge(i);
		this->dataLife->listTrees.push_back(tree);
	}

	this->threadUpdateVege = thread(&Map::runUpdateVege, this);

}

ofVec2f  Map::getPosForest()
{
	return this->posForest;
}
ofVec2f Map::getPosMountain()
{
	return this->posMountain;
}

void Map::runUpdateVege()
{
	int limitGenTree = 0;
	int respanwCooldown = 0;
	while (true)
	{
		this->dataLife->lockListTrees.lock();
		for (list<Vegetable*>::iterator itTree = this->dataLife->listTrees.begin(); itTree != this->dataLife->listTrees.end(); itTree++)
		{
			(*itTree)->aging();
			//Propagation Tree============================================================================
			if ((*itTree)->getAge() > 15 && this->dataLife->listTrees.size() < this->dataLife->limitTrees) {
				Vegetable * tree = new Vegetable(this->vegetalImage);
				tree->setPosition(this->getRandPositionVeget((*itTree)->getOfVec2f(), 85));
				tree->setAge(1);
				if (tree->getOfVec2f().x != 0 && tree->getOfVec2f().y != 0 && limitGenTree < 3) {
					this->dataLife->listTrees.push_front(tree);
				}
				limitGenTree += 1;
			}
			limitGenTree = 0;
		}

		respanwCooldown += 1;
		//Always Tree=============================================================
		if (this->dataLife->listTrees.size() < 10 || respanwCooldown >= 100) {
			respanwCooldown = 0;
			//Forest 
			for (int i = 0; i < 10; i++) {
				Vegetable * tree = new Vegetable(this->vegetalImage);
				tree->setPosition(ToolsLifeGame::getRandomPosition(this->posForest, 250));
				tree->setAge(1);
				this->dataLife->listTrees.push_back(tree);
			}
			//Mountain
			for (int i = 0; i <3; i++) {
				Vegetable * tree = new Vegetable(this->vegetalImage);
				tree->setPosition(ToolsLifeGame::getRandomPosition(this->posMountain, 150));
				tree->setAge(1);
				this->dataLife->listTrees.push_back(tree);
			}
		}
		this->dataLife->lockListTrees.unlock();
		this_thread::sleep_for(chrono::milliseconds(500));
	}
}

void Map::drawCircleMap(ofVec2f pos, ofColor col)
{
	for (int i = 10; i >= 0; i -= 1) {
		ofSetColor(col);
		ofCircle(pos.x, pos.y, (i * 32) + (i*i*i)*1.5f / 10.0f);
	}
}

void Map::draw()
{
	if (this->mapImg != nullptr) {
		ofSetColor(255, 255, 255);
		this->mapImg->draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	if (this->dataLife->showCircleMap) {
		this->drawCircleMap(this->posDessert, ofColor(200, 111, 11, 75));
		this->drawCircleMap(this->posForest, ofColor(55, 200, 11, 75));
		this->drawCircleMap(this->posMountain, ofColor(58, 40, 28, 75));
	}

	//Trees----------------------
	this->dataLife->lockListTrees.lock();
	for (list<Vegetable*>::iterator itTree = this->dataLife->listTrees.begin(); itTree != this->dataLife->listTrees.end(); itTree++)
	{
		(*itTree)->draw();
	}
	this->dataLife->lockListTrees.unlock();

	/*ofBeginShape();
	ofVertex(pp[0]);
	ofSetColor(118,167,198);
	x1 = cos(ofGetElapsedTimef()*moveFreq + 1 )*moveAmplitude;
	y1 = sin(ofGetElapsedTimef()*moveFreq + 1 )*moveAmplitude;
	ofBezierVertex(pp[0].x, pp[0].y, pp[0].x + (-radius * 2 + x1), pp[0].y + (radius*1.9 + y1), pp[1].x + 0, pp[1].y);
	ofBezierVertex(pp[1].x, pp[1].y, pp[1].x + (radius * 2 + x1), pp[1].y + (radius * 2 + y1), pp[2].x, pp[2].y);
	ofBezierVertex(pp[2].x, pp[2].y, pp[2].x + (radius * 2 + x1), pp[2].y + (-radius * 2 + y1), pp[3].x, pp[3].y);
	ofBezierVertex(pp[3].x, pp[3].y, pp[3].x + (-radius * 2 + x1), pp[3].y + (-radius*1.5 + y1), pp[0].x, pp[0].y);
	ofEndShape();

	this->waterImg->draw((pp[0].x + (-radius * 2 + y1)) + 200, (pp[0].y + (radius*1.9 + x1 + y1)) - 150, 50, 25);*/

	/*float x2 = cos(ofGetElapsedTimef()*moveFreq + 4 * 10)*moveAmplitude;
	float y2 = sin(ofGetElapsedTimef()*moveFreq + 4 * 10)*moveAmplitude;

	float x3 = cos(ofGetElapsedTimef()*moveFreq + 3 * 10)*moveAmplitude;
	float y3 = sin(ofGetElapsedTimef()*moveFreq + 3 * 10)*moveAmplitude;

	float x4 = cos(ofGetElapsedTimef()*moveFreq + 4 * 10)*moveAmplitude;
	float y4 = sin(ofGetElapsedTimef()*moveFreq + 4 * 10)*moveAmplitude;*/

}

ofVec2f Map::getRandPositionVeget(ofVec2f pos, int rad)
{
	ofVec2f returnPos;
	returnPos.x = (pos.x + (1 + (rand() % (int)((rad * 2) - 1 + 1)))) - rad;
	returnPos.y = (pos.y + (1 + (rand() % (int)((rad * 2) - 1 + 1)))) - rad;

	for (list<Vegetable*>::iterator itTree = this->dataLife->listTrees.begin(); itTree != this->dataLife->listTrees.end(); itTree++)
	{
		int ii = 0;
		while (!this->positionIsFree((*itTree)->getOfVec2f(), returnPos, 0) && ii < 5) {
			returnPos.x = (pos.x + (1 + (rand() % (int)((rad * 2) - 1 + 1)))) - rad;
			ii += 1;
		}
		if (!this->positionIsFree((*itTree)->getOfVec2f(), returnPos, 0)) {
			returnPos.x = 0;
		}
		ii = 0;
		while (!this->positionIsFree((*itTree)->getOfVec2f(), returnPos, 1) && ii < 5) {
			returnPos.y = (pos.y + (1 + (rand() % (int)((rad * 2) - 1 + 1)))) - rad;
			ii += 1;
		}
		if (!this->positionIsFree((*itTree)->getOfVec2f(), returnPos, 1)) {
			returnPos.y = 0;
		}
	}

	return returnPos;
}

bool Map::positionIsFree(ofVec2f pos1, ofVec2f pos2, char xy)
{
	if (xy == 0) {
		return !ToolsLifeGame::checkCollision(pos1, pos2, 4) && pos2.x < ofGetWidth() && pos2.x > 0;
	}
	else {
		return !ToolsLifeGame::checkCollision(pos1, pos2, 4) && pos2.y < ofGetHeight() && pos2.y > 0;
	}
}

Map::~Map()
{
}
