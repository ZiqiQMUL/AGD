#pragma once
#include "Entity.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/observer/AchievementManager.h"
#include "../../include/observer/Observer.h"

#include <vector>
#include <memory>

// VI.A (2/2): Add a forward declaration to the class PlayerInputHandler
class Fire;
class VelocityComponent;
class PlayerInputHandler;
class InputComponent;
class PlayerStateComponent;


class Player : public Entity
{
public:

    const float playerSpeed = 100.f;
    const int startingHealth = 60;
    const int maxHealth = 100;
    const int maxWood = 100;
    const int shootingCost = 20;
    const float fireSpeed = 200.f;
    const float shootCooldownTime = 3.f; //in seconds

    Player();
    ~Player();

    virtual void init(const std::string& TextureFile, std::shared_ptr<GraphicsComponent> GraphicsComp) override;

    void addWood(int w);

    void positionSprite(int row, int col, int spriteWH, float tileScale);

    bool collidesWith(std::shared_ptr<Entity> _Other);

    std::shared_ptr<Fire> createFire();

    //  Collisions (15%)
    void onPotionCollision(int potionHealthValue)
    {
        // Update player's health.
        dynamic_cast<HealthComponent*>(getComponent(ComponentID::HEALTH))->changeHealth(potionHealthValue);

        // Play sound 
    }

    void onLogCollision()
    {
        // Play sound 
    }

    void notify(const std::string& event);

private:
    std::unique_ptr<Observer> observer;
    std::shared_ptr<AchievementManager> achievementManager;
};
