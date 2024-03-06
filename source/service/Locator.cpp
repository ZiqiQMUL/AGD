#include "../service/Locator.h"

Audio* Locator::service_ = nullptr;
NullAudio Locator::nullService_;

Locator::Locator() { 
	service_ = &nullService_; 
}

Audio& Locator::getAudio() { 
	return *service_; 
}

void Locator::provide(Audio* service) {
	if (service == nullptr)
	{
		service_ = &nullService_;
	}
	else
	{
		service_ = service;
	}
}