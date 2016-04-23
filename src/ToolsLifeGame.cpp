#include "ToolsLifeGame.h"


int ToolsLifeGame::randomBeetwen(int a)
{
	return (int)(rand() % ((2*a)+1) + (-a));
}

float ToolsLifeGame::randomFloat(float a, float b) {
	return a + ((((float)rand()) / (float)RAND_MAX) * (b - a));
}


float ToolsLifeGame::div(float a, float b)
{
	if (b == 0.0f) {
		return 0.0f;
	}
	else {
		return a/b;
	}
}
ofVec2f ToolsLifeGame::getRandomPosition()
{
	ofVec2f returnPos;
	returnPos.x = rand() % ofGetWindowWidth() + 5;
	returnPos.y = rand() % ofGetWindowHeight() + 5;
	return returnPos;
}


ofVec2f ToolsLifeGame::getRandomPosition(ofVec2f pos, int rad, bool compress)
{
	ofVec2f returnPos;
	float x = 0.0f;
	float y = 0.0f;
	if (compress) {
		x = (randomFloat())*cos(randomFloat(0.0f, 2.0f*PI));//[-1,1]
		y = (randomFloat())*sin(randomFloat(0.0f, 2.0f*PI));
	}
	else {
		x = sqrt(randomFloat())*cos(randomFloat(0.0f, 2.0f*PI));
		y = sqrt(randomFloat())*sin(randomFloat(0.0f, 2.0f*PI));
	}
	returnPos.x = (float)pos.x + (float)((float)rad * x); //(float)(pos.x + (float)randomBeetwen(rad));//(float)(pos.x + (1 + (rand() % (int)((rad * 2) - 1 + 1)))) - rad;
	returnPos.y = (float)pos.y + (float)((float)rad * y); //(float)(pos.y + (float)randomBeetwen(rad));//(float)(pos.y + (1 + (rand() % (int)((rad * 2) - 1 + 1)))) - rad;

	//X---------------------------------------------------
	if (returnPos.x > (float)ofGetWindowWidth()) {
		returnPos.x = ((float)ofGetWindowWidth()) - ((float)(rand()%15)) ;
		/*while (returnPos.x > (ofGetWindowWidth() - 5.0f)) {
			returnPos.x -= 5.0f;
		}*/
	}
	if (returnPos.x < (float)5.0f) {
		returnPos.x = (rand() % 15);
		/*while (returnPos.x < 5.0f) {
			returnPos.x += 5.0f;
		}*/
	}
	
	//Y----------------------------------------------
	if (returnPos.y > (float)ofGetWindowHeight()) {
		returnPos.y = ((float)ofGetWindowHeight()) - ((float)(rand() % 15));
	}
	if (returnPos.y < (float)5.0f) {
		returnPos.y = (float)(rand() % 15);
	}

	return returnPos;
}

ofVec2f ToolsLifeGame::getHalfPath(ofVec2f pos1, ofVec2f pos2)
{
	ofVec2f posR;
	posR.x = pos1.x + ((pos2.x - pos1.x) / 2.0f);
	posR.y = pos1.y + ((pos2.y - pos1.y) / 2.0f);
	/*
	posR.x = pos1.x + (sqrt(pow((pos1.x - pos2.x), 2)) / 2.0f);
	posR.y = pos1.y + (sqrt(pow((pos1.y - pos2.y), 2)) / 2.0f);*/
	return posR;
}

bool ToolsLifeGame::checkCollision(ofVec2f pos1, ofVec2f pos2, int rad)
{
	return ((pos2.x - pos1.x)*(pos2.x - pos1.x) + (pos2.y - pos1.y)*(pos2.y - pos1.y)) < rad*rad;
	//return !((pos1.y + rad) <= (pos2.y - rad) || (pos1.y - rad) >= (pos2.y + rad) || (pos1.x + rad) <= (pos2.x - rad) || (pos1.x - rad) >= (pos2.x + rad));
}

bool ToolsLifeGame::circlesColliding(ofVec2f pos1, ofVec2f pos2, int rad1, int rad2)
{
	//compare the distance to combined radii
	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	int radii = rad1 + rad2;
	return ((dx * dx) + (dy * dy) < radii * radii);

}

bool ToolsLifeGame::arCCollision(ofVec2f pos1, float angl, int visionA, int rad, ofVec2f pos2)
{
	//circlesColliding()
	if (ToolsLifeGame::circlesColliding(pos1, pos2, rad)) {
		float ang = atan2f(pos2.y - pos1.y, pos2.x - pos1.x)* (180.0f / PI);
		return (ang > (angl - (visionA / 2)) && ang < (angl + (visionA / 2)));
	}
	return false;
}

float ToolsLifeGame::getDistance(ofVec2f pos1, ofVec2f pos2)
{
	return sqrt(pow((pos1.x - pos2.x), 2) + pow((pos1.y - pos2.y), 2));
}

