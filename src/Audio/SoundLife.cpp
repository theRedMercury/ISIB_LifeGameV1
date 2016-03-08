#include "SoundLife.h"

SoundLife::SoundLife(float vol)
{
	this->volum = vol;
	soundMainAmbi.loadSound("melody.ogg");
	soundMainAmbi.setVolume(0.45*this->volum);
	soundMainAmbi.setSpeed(1.0f);
	soundMainAmbi.setLoop(true);
	soundMainAmbi.play();


	soundEatTree1.loadSound("meld0.ogg");
	soundEatTree1.setVolume(1.0*this->volum);
	soundEatTree1.setSpeed(1.0f);
	soundEatTree1.play();

	soundEatTree2.loadSound("LifeSound2.ogg");
	soundEatTree2.setVolume(0.1*this->volum);
	soundEatTree2.setSpeed(0.9f);

	soundEatTree3.loadSound("LifeSound3.ogg");
	soundEatTree3.setVolume(0.1*this->volum);
	soundEatTree3.setSpeed(0.9f);
	
	soundEatHerbi1.loadSound("LifeSoundEat1.ogg");
	soundEatHerbi1.setVolume(0.1*this->volum);
	soundEatHerbi1.setSpeed(0.9f);

	soundEatHerbi2.loadSound("LifeSoundEat2.ogg");
	soundEatHerbi2.setVolume(0.1*this->volum);
	soundEatHerbi2.setSpeed(0.9f);

	soundEatHerbi3.loadSound("LifeSoundEat3.ogg");
	soundEatHerbi3.setVolume(0.1*this->volum);
	soundEatHerbi3.setSpeed(0.9f);
	//soundPlayer.play();  
}

//Pan = -1.0 Left	0.0 = Center	1.0 = Right
void SoundLife::playSoundEatVeg(float pan)
{
	int sR = rand() % 3;
	//float pSound = ((rand() % 2000)-1000.0)/2.0f
	switch (sR) {
	case 0:
		if (!soundEatTree1.isPlaying()) {
			soundEatTree1.setPan(pan);
			soundEatTree1.play();
		}
		break;
	case 1:
		if (!soundEatTree2.isPlaying()) {
			soundEatTree2.setPan(pan);
			soundEatTree2.play();
		}
		break;
	case 2:
		if (!soundEatTree3.isPlaying()) {
			soundEatTree3.setPan(pan);
			soundEatTree3.play();
		}
		break;
	default:
		if (!soundEatTree1.isPlaying()) {
			soundEatTree1.setPan(pan);
			soundEatTree1.play();
		}
		break;
	}
	
}

void SoundLife::playSoundEatHerbi(float pan)
{
	int sR = rand() % 3;
	switch (sR) {
	case 0:
		if (!soundEatHerbi1.isPlaying()) {
			soundEatHerbi1.setPan(pan);
			soundEatHerbi1.play();
		}
		break;
	case 1:
		if (!soundEatHerbi2.isPlaying()) {
			soundEatHerbi2.setPan(pan);
			soundEatHerbi2.play();
		}
		break;
	case 2:
		if (!soundEatHerbi3.isPlaying()) {
			soundEatHerbi3.setPan(pan);
			soundEatHerbi3.play();
		}
		break;
	default:
		if (!soundEatHerbi1.isPlaying()) {
			soundEatTree1.setPan(pan);
			soundEatHerbi1.play();
		}
		break;
	}
}

SoundLife::~SoundLife()
{
}
