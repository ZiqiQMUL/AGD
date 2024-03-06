#include "../service/Audio.h"


void NullAudio::playAudio(AUDIO_TYPE) {}

void NullAudio::stopAudio(AUDIO_TYPE) {}

ConsoleAudio::ConsoleAudio()
{
	potion.loadFromFile("audio/potion.wav");
	fire.loadFromFile("audio/fire.wav");
	axe.loadFromFile("audio/axe.wav");
	audioPotion.setBuffer(potion);
	audioFire.setBuffer(fire);
	audioAxe.setBuffer(axe);
}

void ConsoleAudio::playAudio(AUDIO_TYPE _Audio)
{
	switch (_Audio)
	{
	case AUDIO_TYPE::POTION:
		audioPotion.play();
		break;
	case AUDIO_TYPE::FIRE:
		audioFire.play();
		break;
	case AUDIO_TYPE::AXE:
		audioAxe.play();
		break;
	default:
		break;
	}
}

void ConsoleAudio::stopAudio(AUDIO_TYPE _Audio)
{
	switch (_Audio)
	{
	case AUDIO_TYPE::POTION:
		audioPotion.stop();
		break;
	case AUDIO_TYPE::FIRE:
		audioFire.stop();
		break;
	case AUDIO_TYPE::AXE:
		audioAxe.stop();
		break;
	default:
		break;
	}
}