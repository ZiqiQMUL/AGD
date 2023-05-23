#include "../../include/systems/Systems.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/core/Game.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "SFML/Graphics.hpp"

GraphicsSystem::GraphicsSystem()
{
	componentMask.turnOnBit(static_cast<int>(ComponentID::POSITION));
	componentMask.turnOnBit(static_cast<int>(ComponentID::GRAPHICS));
}

void GraphicsSystem::update(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed)
{
	auto pComp = dynamic_cast<const PositionComponent*>(_Entity->getComponent(ComponentID::POSITION));
	if (pComp == nullptr)
		throw std::exception("Null Position Component");

	auto gComp = dynamic_cast<GraphicsComponent*>(_Entity->getComponent(ComponentID::GRAPHICS));
	if (gComp == nullptr)
		throw std::exception("Null Graphics Component");

	auto& position = pComp->getPosition();
	try
	{
		auto& ss = gComp->getSpriteSheet();
		ss.setSpritePosition(sf::Vector2f(position.x, position.y));
		ss.update(_Elapsed);
	}
	catch (...)
	{
		//not animated
		gComp->getSprite().setPosition(position.x, position.y);
	}

	_Game->getWindow()->draw(gComp->getSprite());
}