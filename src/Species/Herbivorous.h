#pragma once

#include "Animal.h"

namespace lifeGame {
	class Herbivorous : public Animal
	{

	public:
		Herbivorous(Herbivorous * mama = nullptr, ofImage * img = nullptr, ToolsLifeGame * tool = nullptr, int numP = -1);
		void eating(unsigned char en = 1);
		void aging();
		void setAge(unsigned char age = 1);
		void setNextDesti(ofVec2f n);
		float getUpdAnim();
		void updateMove();
		void update();
		void draw();
		~Herbivorous();


	private:
		void updateAge();
		unsigned char radiusC = 6;

		float getPt(float n1, float n2, float perc);

		ofVec2f x1;
		ofVec2f x2;
		ofVec2f x3;
		ofVec2f x4;

		ofVec2f old;
		float angl = 0.0f;

		float  updAnim = 0.0;
		Herbivorous * mother = nullptr;
	};

}