#include "SoundLife.h"

SoundLife::SoundLife(float vol)
{
	this->volum = vol;
	string name("meld");
	string ext(".ogg");
	for (char i = '0'; i <= '8'; i++) {
		this->soundName.push_back(name + i + ext);
	}

	this->soundListEatTree.push_back("eatT1.wav");
	this->soundListEatTree.push_back("eatT2.wav");
	this->soundListEatTree.push_back("eatT3.wav");
	this->soundListEatHerbi.push_back("eatH1.wav");
	this->soundListEatHerbi.push_back("eatH2.wav");
	this->soundListEatHerbi.push_back("eatH3.wav");

	this->soundEatTree.loadSound(this->soundListEatTree.at(this->indexSound));
	this->soundEatHerbi.loadSound(this->soundListEatHerbi.at(this->indexSound));
	this->soundEatTree.setVolume(1.0f*this->volum);
	this->soundEatTree.setSpeed(1.0f);

	this->soundEatHerbi.setVolume(1.0f*this->volum);
	this->soundEatHerbi.setSpeed(1.0f);
	

	this->soundMainAmbi.loadSound("melody.ogg");
	this->soundMainAmbi.setVolume(1.0f*this->volum);
	this->soundMainAmbi.setSpeed(1.0f);
	this->soundMainAmbi.setLoop(true);
	this->soundMainAmbi.play();

	this->soundStartInvad.loadSound("invade.ogg");
	this->soundStartInvad.setVolume(1.0f*this->volum);
	this->soundStartInvad.setSpeed(1.0f);

	this->soundMainInvad.loadSound("invade2.wav");
	this->soundMainInvad.setVolume(1.0f*this->volum);
	this->soundMainInvad.setSpeed(1.0f);


	this->soundMainMelody.setVolume(0.7f*this->volum);
	this->soundMainMelody.setSpeed(1.0f);
	this->soundMelodyRun = thread(&SoundLife::runMainMelody, this);

	//soundPlayer.play();  
}

void SoundLife::runMainMelody()
{
	int listRand[9] = { 0, 1, 2, 3, 4, 5, 6, 7,8};
	srand(unsigned(time(0)));
	random_shuffle(listRand, listRand + 9);
	
	/*for (int i = 0; i <= 8; i++) {
		cout << listRand[i] << "-";
	}
	cout << endl;*/

	int compt = 0;
	this_thread::sleep_for(chrono::milliseconds(5000));
	while (this->running) {
		this->soundMainMelody.loadSound(this->soundName.at(listRand[compt]));
		this->soundMainMelody.play();
		compt += 1;

		while (this->soundMainMelody.isPlaying() && this->running)
		{
			this_thread::sleep_for(chrono::milliseconds(3000));
			if (!this->soundStartInvad.isPlaying() && !this->soundMainInvad.isPlaying()) {
				this->lockLevelSet.lock();
				this->soundMainMelody.setVolume(7.0f*this->volum);
				this->lockLevelSet.unlock();
			}
		}
		this_thread::sleep_for(chrono::milliseconds(10000+(rand() % 8000)));
		if (compt > 8) {
			srand(unsigned(time(0)));
			random_shuffle(listRand, listRand + 9);
			compt = 0;
		}
	}
}

//Pan = -1.0 Left	0.0 = Center	1.0 = Right
void SoundLife::playSoundEatVeg(float pan)
{
	if (!this->soundEatTree.isPlaying()) {
		this->indexSound += 1;
		if (this->indexSound > 2) {
			this->indexSound = 0;
		}
		this->soundEatTree.loadSound(this->soundListEatTree.at(this->indexSound));
	}
	if (!this->soundEatTree.isPlaying()) {
		this->soundEatTree.setPan(pan);
		this->soundEatTree.play();
		
	}
}

void SoundLife::playSoundEatHerbi(float pan)
{
	if (!this->soundEatHerbi.isPlaying()) {
		this->soundEatHerbi.loadSound(this->soundListEatHerbi.at(this->indexSound));
	}
	if (!this->soundEatHerbi.isPlaying()) {
		this->soundEatHerbi.setPan(pan);
		this->soundEatHerbi.play();
	}
}

void SoundLife::playSoundStartInvade()
{
	this->soundStartInvad.play();
	this->soundMainInvad.play();
	this->lockLevelSet.lock();
	this->soundMainMelody.setVolume(0.5f*this->volum);
	this->lockLevelSet.unlock();
}

SoundLife::~SoundLife()
{
	this->running = false;
	this->soundMainAmbi.stop();
	this->soundMainMelody.stop();
	this->soundStartInvad.stop();
	this->soundMainInvad.stop();

	this->soundEatTree.stop();
	this->soundEatHerbi.stop();
}
