#pragma once

#include "Species.h"
#include "SoundLife.h"
#define BOOL_MF(bool_expr) "%s=%s\n", #bool_expr, (bool_expr) ? "Male" : "Female"


class Animal : public Species
{

public:
	Animal();
	bool babyReady();
	void babyBorn();
	void setPosition(ofVec2f pos);
	void eating(float en = 25.0f);
	void updateGestation(int decr = 1);
	void duplication();
	unsigned char getEnergy();
	~Animal();


	//Virtual
	virtual void aging() = 0;
	virtual void updateAnimation() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

protected:

	bool getSexe();
	bool getEatFound();
	void setEatFound(bool b = false);
	bool getWantEat();
	void setWantEat(bool b = false);
	bool getEatLock();
	void setEatLock(bool b = false);
	bool getPregnant();
	void setPregnant(bool b = false);
	bool getWantDuplicate();
	void setWantDuplicate(bool b = false);

	float getPointPercent(float n1, float n2, float perc);
	

	//int numPack = -1;		//
	float pregnancy;		// 0=Free
	float energy;			// 0-100%
	unsigned char ageDead;	//Random (age-10)& (age+10)

	float speedMov;
	float percentAnim;		//0-100%

	ofPath * circleDetect = nullptr;
	ofPath * vision = nullptr;
	SoundLife * soundL = nullptr;

private:
	bitset<8> statut;		// XXX : [0]=Sexe / [1]=EatFound / [2]=...
};

