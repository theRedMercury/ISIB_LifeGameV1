#pragma once

#include "ofMain.h"


class SoundLife
{
public:
	SoundLife(float vol = 1.0);

	void playSoundEatVeg(float pan = 1.0);
	void playSoundEatHerbi(float pan = 1.0);
	~SoundLife();

private:
	float volum = 1.0;
	ofSoundPlayer soundMainAmbi;

	ofSoundPlayer soundEatTree1;
	ofSoundPlayer soundEatTree2;
	ofSoundPlayer soundEatTree3;

	ofSoundPlayer soundEatHerbi1;
	ofSoundPlayer soundEatHerbi2;
	ofSoundPlayer soundEatHerbi3;
};

