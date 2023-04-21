#pragma once
#include "../../include/components/HealthComponent.h"
#include "Entity.h"

class Fire;

// VI.A (2/2): Add a forward declaration to the class PlayerInputHandler
class PlayerInputComponent;
class VelocityComponent;
class PlayerStateComponent;

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

	virtual void update(Game* game, float elapsed = 1.0f) override;
	virtual void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc) override;

	virtual void draw(Window* window) override;

	void handleInput(Game& game);

	std::shared_ptr<HealthComponent> getHealthComp() { return health; }

	void addWood(int w);

	void positionSprite(int row, int col, int spriteWH, float tileScale);

	auto& getVelocityComp() { return velocity; }

	std::shared_ptr<ColliderComponent> getColliderComp()override { return collider; }

	std::shared_ptr<PlayerStateComponent> getStateComp() { return state; }

	bool collidesWith(std::shared_ptr<Entity> _Other);

	std::shared_ptr<Fire> createFire() const;

private:


	std::shared_ptr<HealthComponent> health;
	std::shared_ptr<VelocityComponent> velocity;

	// VI.A (1/2): Declare a unique pointer to a player input handler.
	std::unique_ptr<PlayerInputComponent> input;

	std::shared_ptr<ColliderComponent> collider;

	std::shared_ptr<PlayerStateComponent> state;
};

