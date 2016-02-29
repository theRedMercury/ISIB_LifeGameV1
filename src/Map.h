#pragma once

#include "ofMain.h"
#include "DataLife.h"
namespace lifeGame {
	class Map
	{
	public:
		Map(DataLife * dataL);

		ofVec2f getPosForest();
		ofVec2f getPosMountain();
		void draw();
		~Map();

	private:
		void runUpdateVege();
		void drawCircleMap(ofVec2f pos, ofColor col);
		ofVec2f getRandPositionVeget(ofVec2f pos, int rad);
		bool positionIsFree(ofVec2f pos1, ofVec2f pos2, char xy);

		ofImage * mapImg = nullptr;
		ofImage * waterImg = nullptr;
		ofImage * vegetalImage = nullptr;

		DataLife * dataLife = nullptr;

		ofVec2f posForest;
		ofVec2f posMountain;
		ofVec2f posDessert;

		mutex lockListTrees;
		thread threadUpdateVege;
		list<Vegetable*> listTrees;


		vector<ofPoint> pp = { ofPoint(150,ofGetHeight() - 325),ofPoint(150,ofGetHeight() - 50) ,ofPoint(750,ofGetHeight() - 75),ofPoint(545,ofGetHeight() - 390) };
		float radius = 90;
		float moveFreq = 4;
		float moveAmplitude = 2;
		float x1, y1;

	};
}

