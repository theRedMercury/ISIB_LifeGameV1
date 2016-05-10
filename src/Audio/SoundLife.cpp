#include "SoundLife.h"

SoundLife::SoundLife(float mVol, float aVol, float melVol, float inVol, float eatVol, float speedS)
{
	this->mainVol = mVol;
	this->ambiVol = aVol;
	this->meloVol = melVol;
	this->invaVol = inVol;
	this->eatiVol = eatVol;

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
	this->soundEatTree.setVolume(this->mainVol*this->eatiVol);
	this->soundEatTree.setSpeed(speedS);

	this->soundEatHerbi.loadSound(this->soundListEatHerbi.at(this->indexSound));
	this->soundEatHerbi.setVolume(this->mainVol*this->eatiVol);
	this->soundEatHerbi.setSpeed(speedS);
	

	this->soundMainAmbi.loadSound("mainMelody.wav");
	this->soundMainAmbi.setVolume(this->mainVol*this->ambiVol);
	this->soundMainAmbi.setSpeed(speedS);
	this->soundMainAmbi.setLoop(true);
	this->soundMainAmbi.play();

	this->soundInvad.loadSound("invadeMain.wav");
	this->soundInvad.setVolume(this->mainVol*this->invaVol);
	this->soundInvad.setSpeed(speedS);


	this->soundMainMelody.setVolume(this->mainVol*this->meloVol);
	this->soundMainMelody.setSpeed(speedS);
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
			if (!this->soundInvad.isPlaying()) {
				this->lockLevelSet.lock();
				this->soundMainMelody.setVolume(this->mainVol*this->meloVol);
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
	this->soundInvad.play();
	this->lockLevelSet.lock();
	this->soundMainMelody.setVolume(this->mainVol*this->meloVol*0.3f);
	this->lockLevelSet.unlock();
}

SoundLife::~SoundLife()
{
	this->running = false;
	this->soundMainAmbi.stop();
	this->soundMainMelody.stop();
	this->soundInvad.stop();


	this->soundEatTree.stop();
	this->soundEatHerbi.stop();
}
