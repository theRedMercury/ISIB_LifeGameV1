#pragma once

#include "ofMain.h"

//URL SOUND https://soundcloud.com/nicolas-masson-887579839/sets/first-test-piano

class SoundLife
{
public:
	SoundLife(float vol = 1.0);

	void playSoundEatVeg(float pan = 1.0);
	void playSoundEatHerbi(float pan = 1.0);
	void playSoundStartInvade();
	~SoundLife();

private:

	void runMainMelody();

	float volum = 1.0;
	bool running = true;
	vector<string> soundName;

	ofSoundPlayer soundMainAmbi;
	ofSoundPlayer soundMainMelody;
	ofSoundPlayer soundStartInvad;

	thread soundMelodyRun;
};

