#include "../../include/systems/Systems.h"
#include "../../include/core/Game.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/TTLComponent.h"
#include "SFML/Graphics.hpp"

ColliderSystem::ColliderSystem() {
    addComponentToMask(ComponentID::COLLIDER);
    addComponentToMask(ComponentID::POSITION);
}

void ColliderSystem::updateComponents(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed) {
    auto positionComp = getComponentAndCheck<PositionComponent>(_Entity.get(), ComponentID::POSITION);
    auto colliderComp = getComponentAndCheck<BoxColliderComponent>(_Entity.get(), ComponentID::COLLIDER);

    auto& position = positionComp->getPosition();
    colliderComp->setBoxPosition(position);
}

GameplaySystem::GameplaySystem() {
    addComponentToMask(ComponentID::LOGIC);
}

void GameplaySystem::updateComponents(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed) {
    auto logicComp = getComponentAndCheck<PlayerStateComponent>(_Entity.get(), ComponentID::LOGIC);

    logicComp->update(_Game, _Entity.get(), _Elapsed);
}

GraphicsSystem::GraphicsSystem() {
    addComponentToMask(ComponentID::POSITION);
    addComponentToMask(ComponentID::GRAPHICS);
}

void GraphicsSystem::updateComponents(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed) {
    auto positionComp = getComponentAndCheck<PositionComponent>(_Entity.get(), ComponentID::POSITION);
    auto graphicsComp = getComponentAndCheck<GraphicsComponent>(_Entity.get(), ComponentID::GRAPHICS);

    auto& position = positionComp->getPosition();
    try
    {
        auto& ss = graphicsComp->getSpriteSheet();
        ss.setSpritePosition(sf::Vector2f(position.x, position.y));
        ss.update(_Elapsed);
    }
    catch (...)
    {
        graphicsComp->getSprite().setPosition(position.x, position.y);
    }

    _Game->getWindow()->draw(graphicsComp->getSprite());
}

InputSystem::InputSystem() {
    addComponentToMask(ComponentID::INPUT);
    addComponentToMask(ComponentID::VELOCITY);
}

void InputSystem::updateComponents(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed) {
    auto velocityComponent = getComponentAndCheck<VelocityComponent>(_Entity.get(), ComponentID::VELOCITY);
    auto inputComponent = getComponentAndCheck<InputComponent>(_Entity.get(), ComponentID::INPUT);

    velocityComponent->setVelocity(0.0f, 0.0f);

    auto cmds = inputComponent->getHandler()->handleInput();
    for (auto& cmd : cmds)
    {
        cmd->execute(*_Game);
    }
}

MovementSystem::MovementSystem() {
    addComponentToMask(ComponentID::POSITION);
    addComponentToMask(ComponentID::VELOCITY);
}

void MovementSystem::updateComponents(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed) {
    auto velocityComp = getComponentAndCheck<VelocityComponent>(_Entity.get(), ComponentID::VELOCITY);
    auto positionComp = getComponentAndCheck<PositionComponent>(_Entity.get(), ComponentID::POSITION);

    auto movement = velocityComp->getVelocity() * _Elapsed * velocityComp->getSpeed();
    auto newPosition = positionComp->getPosition() + movement;
    positionComp->setPosition(newPosition.x, newPosition.y);
}

PrintDebugSystem::PrintDebugSystem() {
    addComponentToMask(ComponentID::COLLIDER);
}

void PrintDebugSystem::updateComponents(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed) {
    auto colliderComponent = getComponentAndCheck<BoxColliderComponent>(_Entity.get(), ComponentID::COLLIDER);

    _Game->getWindow()->draw(colliderComponent->getDrawableRect());
}

TTLSystem::TTLSystem() {
    addComponentToMask(ComponentID::TTL);
}

void TTLSystem::updateComponents(Game* _Game, std::shared_ptr<Entity> _Entity, float _Elapsed) {
    auto ttlComponent = getComponentAndCheck<TTLComponent>(_Entity.get(), ComponentID::TTL);

    ttlComponent->decreaseTTL();
    if (ttlComponent->getTTL() <= 0)
    {
        _Entity->deleteEntity();
    }
}