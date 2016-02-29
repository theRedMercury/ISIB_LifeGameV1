#pragma once
#include "ofMain.h"

namespace lifeGame {
	class ToolsLifeGame
	{
	public:
		//Static
		ToolsLifeGame();
		static float div(float a = 1.0f, float b = 1.0f);
		static ofVec2f getRandomPosition();
		static ofVec2f getRandomPosition(ofVec2f pos, int rad = 10);

		static bool checkCollision(ofVec2f pos1, ofVec2f pos2, int rad = 5);
		static bool circlesColliding(ofVec2f pos1, ofVec2f pos2, int rad1 = 5, int rad2 = 5);
		static bool shapeCollision(ofPath path1, ofPath path2);

		static const unsigned char BaseTri = 6;
		static const unsigned char HeightTri = 10;
		static const unsigned char SquarHW = 12;
		static const unsigned char RadiusC = 6;

	private:
		static int randomBeetwen(int a);
	};
}

