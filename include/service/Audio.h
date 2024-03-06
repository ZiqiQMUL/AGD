#pragma once
#include <SFML/Audio.hpp>
//reference Game Programming Patterns by Bob Nystrom

enum class AUDIO_TYPE
{
	POTION,
	FIRE,
	AXE,
};

class Audio {
public:
	virtual ~Audio() {}
	virtual void playAudio(AUDIO_TYPE) = 0;
	virtual void stopAudio(AUDIO_TYPE) = 0;
};

class NullAudio : public Audio {
public:
	virtual void playAudio(AUDIO_TYPE);
	virtual void stopAudio(AUDIO_TYPE);
};

class ConsoleAudio :public Audio {
public:
	ConsoleAudio();
	virtual void playAudio(AUDIO_TYPE _Audio);
	virtual void stopAudio(AUDIO_TYPE _Audio);

private:
	sf::Sound audioPotion;
	sf::Sound audioFire;
	sf::Sound audioAxe;
	sf::SoundBuffer potion;
	sf::SoundBuffer fire;
	sf::SoundBuffer axe;
};