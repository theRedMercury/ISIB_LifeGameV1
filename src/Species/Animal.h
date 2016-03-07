#pragma once

#include "Species.h"

#define BOOL_MF(bool_expr) "%s=%s\n", #bool_expr, (bool_expr) ? "Male" : "Female"


class Animal : public Species
{

public:
	Animal();
	bool babyReady();
	void babyBorn();
	void setPosition(ofVec2f pos);
	void setEnergy(unsigned char en);
	void updateGestation(int decr = 1);
	void duplication();
	unsigned char getEnergy();
	~Animal();


	//Virtual
	virtual void eating(unsigned char en = 1) = 0;
	virtual void aging() = 0;
	virtual void updateAge() =0;
	virtual void updateMove() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

protected:
	bool getSexe();
	bool getEatFound();
	void setEatFound(bool b = false);
	bool getWantEat();
	void setWantEat(bool b = false);
	bool getPregnant();
	void setPregnant(bool b = false);
	bool getWantDuplicate();
	void setWantDuplicate(bool b = false);
	

	//int numPack = -1;		//

	int pregnancy;			// 0=Free
	unsigned char energy;	// 0-255
	unsigned char ageDead;	//Random (age-10)& (age+10)

	float speedMov;
	ofVec2f nextDesti;
	ofPath * circleDetect = nullptr;
	ofPath * vision = nullptr;
	ToolsLifeGame * tools = nullptr;

private:
	bitset<8> statut;		// XXX : [0]=Sexe / [1]=EatFound / [2]=...
};

