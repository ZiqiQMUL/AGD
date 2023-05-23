#include "../../include/components/InputComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/core/Game.h"
#include "../../include/core/InputHandler.h"

PlayerInputComponent::PlayerInputComponent()
{
	input = std::make_unique<PlayerInputHandler>();
}


std::shared_ptr<PlayerInputHandler> PlayerInputComponent::getHandler()
{
	return input;
}