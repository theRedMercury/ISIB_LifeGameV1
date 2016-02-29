#pragma once

#include "Species.h"

#define BOOL_MF(bool_expr) "%s=%s\n", #bool_expr, (bool_expr) ? "Male" : "Female"

class Animal : public Species
{

public:
	Animal();
	bool getSexe();
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
	virtual void updateMove() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

protected :

	bool sexe;				//0=M / 1=F
	bool pregnant;			// % Gestation 
	int pregnancy;			// 0=Free
	int numPack = -1;		//
	bitset<8> statut;		// XXX : [0]=Move / [1]=Reproduction / [2]=predation
	unsigned char energy;	// 0-255
	unsigned char ageDead;	//Random (age-10)& (age+10)
	ofVec2f nextDesti;
	float speedMov;
	ofPath * circleDetect = nullptr;
	ofPath * vision = nullptr;
	ToolsLifeGame * tools = nullptr;
};

