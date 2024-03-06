#pragma once
#include "../service/Audio.h"

class Locator
{
public:
	Locator();
	static Audio& getAudio();
	static void provide(Audio* service);

private:
	static Audio* service_;
	static NullAudio nullService_;
};