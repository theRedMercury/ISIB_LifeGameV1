#pragma once

#include "ofMain.h"

//URL SOUND https://soundcloud.com/nicolas-masson-887579839/sets/first-test-piano

class SoundLife
{
public:
	SoundLife(float mVol = 1.0, float aVol = 1.0, float melVol = 1.0, float inVol = 1.0, float eatVol = 1.0, float speedS = 1.0);

	void playSoundEatVeg(float pan = 1.0);
	void playSoundEatHerbi(float pan = 1.0);
	void playSoundStartInvade();
	~SoundLife();

private:

	void runMainMelody();

	float mainVol = 1.0;
	float ambiVol = 1.0;
	float meloVol = 1.0;
	float invaVol = 1.0;
	float eatiVol = 1.0;

	bool running = true;
	unsigned int indexSound = 0;

	vector<string> soundName;
	vector<string> soundListEatTree;
	vector<string> soundListEatHerbi;

	ofSoundPlayer soundMainAmbi;
	ofSoundPlayer soundMainMelody;
	ofSoundPlayer soundStartInvad;
	ofSoundPlayer soundMainInvad;

	ofSoundPlayer soundEatTree;
	ofSoundPlayer soundEatHerbi;

	thread soundMelodyRun;
	mutex lockLevelSet;
};

