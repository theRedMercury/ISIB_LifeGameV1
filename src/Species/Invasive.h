#pragma once

#include "Animal.h"

namespace lifeGame {
	class Invasive : public Animal
	{

	public:
		Invasive();
		void eating(unsigned char en);
		void aging();
		void updateMove();
		void update();
		void draw();
		~Invasive();
	};
}

