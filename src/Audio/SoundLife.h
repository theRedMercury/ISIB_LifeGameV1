#pragma once

#include "ofMain.h"

#include <string>

class SoundLife
{
public:
	SoundLife(float vol = 1.0);

	void playSoundEatVeg(float pan = 1.0);
	void playSoundEatHerbi(float pan = 1.0);
	~SoundLife();

private:

	void runMainMelody();


	float volum = 1.0;
	vector<string> soundName;

	ofSoundPlayer soundMainAmbi;
	ofSoundPlayer soundMainMelody;

	thread soundMelodyRun;

};

