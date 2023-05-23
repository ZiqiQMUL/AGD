#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/VelocityComponent.h"

InputSystem::InputSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::INPUT));
	componentMask.turnOnBit(static_cast<int>(ComponentID::VELOCITY));
}

void InputSystem::update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed)
{
	auto velocity = dynamic_cast<VelocityComponent*>(_Entity->getComponent(ComponentID::VELOCITY));
	if (velocity == nullptr)
		throw std::exception("Null Velocity Component");
	velocity->setVelocity(0.0f, 0.0f);;

	auto input = dynamic_cast<InputComponent*>(_Entity->getComponent(ComponentID::INPUT));
	if(input==nullptr)
		throw std::exception("Null Input Component");

	auto cmds = input->getHandler()->handleInput();
	for (auto& cmd : cmds)
	{
		cmd->execute(*_Game);
	}
}