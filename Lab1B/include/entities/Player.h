#pragma once
#include "../../include/components/HealthComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/LogicComponent.h"
#include "../../include/components/InputComponent.h"
#include "Entity.h"

class Fire;

// VI.A (2/2): Add a forward declaration to the class PlayerInputHandler
class VelocityComponent;

class Player :  public Entity
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

	virtual void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override;

	void addWood(int w);

	void positionSprite(int row, int col, int spriteWH, float tileScale);

	bool collidesWith(std::shared_ptr<Entity> _Other);

	std::shared_ptr<Fire> createFire() const;

};

