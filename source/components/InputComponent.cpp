#include "../components/InputComponent.h"
#include "../components/VelocityComponent.h"
#include "../core/Game.h"
//#include "../core/Command.h"


PlayerInputComponent::PlayerInputComponent()
{
	input = std::make_unique<PlayerInputHandler>();
}


std::shared_ptr<PlayerInputHandler> PlayerInputComponent::getHandler()
{
	return input;
}