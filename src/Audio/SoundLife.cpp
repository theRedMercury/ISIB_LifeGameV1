#include "SoundLife.h"

SoundLife::SoundLife(float vol)
{
	this->volum = vol;
	string name("meld");
	string ext(".ogg");
	for (char i = '0'; i <= '8'; i++) {
		this->soundName.push_back(name + i + ext);
	}

	this->soundMainAmbi.loadSound("melody.ogg");
	this->soundMainAmbi.setVolume(0.45f*this->volum);
	this->soundMainAmbi.setSpeed(1.0f);
	this->soundMainAmbi.setLoop(true);
	this->soundMainAmbi.play();

	this->soundStartInvad.loadSound("invade.ogg");
	this->soundStartInvad.setVolume(1.0f*this->volum);
	this->soundStartInvad.setSpeed(1.0f);


	this->soundMainMelody.setVolume(1.0f*this->volum);
	this->soundMainMelody.setSpeed(1.0f);
	this->soundMelodyRun = thread(&SoundLife::runMainMelody, this);

	//soundPlayer.play();  
}

void SoundLife::runMainMelody()
{
	int listRand[9] = { 0, 1, 2, 3, 4, 5, 6, 7,8};
	srand(unsigned(time(0)));
	random_shuffle(listRand, listRand + 9);
	for (int i = 0; i <= 8; i++) {
		cout << listRand[i] << "-";
	}
	cout << endl;
	int compt = 0;
	while (true) {
		this->soundMainMelody.loadSound(this->soundName.at(listRand[compt]));
		this->soundMainMelody.play();
		compt += 1;

		while (this->soundMainMelody.isPlaying())
		{
			this_thread::sleep_for(chrono::milliseconds(3000));
		}
		this_thread::sleep_for(chrono::milliseconds(10000+(rand() % 8000)));
		if (compt > 8) {
			srand(unsigned(time(0)));
			random_shuffle(listRand, listRand + 9);
			for (int i = 0; i <= 8; i++) {
				cout << listRand[i] << "-";
			}
			cout << endl;
			compt = 0;
		}
		
	}
}

//Pan = -1.0 Left	0.0 = Center	1.0 = Right
void SoundLife::playSoundEatVeg(float pan)
{
	
}

void SoundLife::playSoundEatHerbi(float pan)
{
	
}

void SoundLife::playSoundStartInvade()
{
	this->soundStartInvad.play();
}

SoundLife::~SoundLife()
{
}
