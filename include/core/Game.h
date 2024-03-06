#pragma once
#include "../components/PlayerStateComponent.h"
#include "../graphics/Window.h"
#include "../core/InputHandler.h"
#include "../core/Board.h"
#include "../entities/Player.h"
#include "../systems/Systems.h"
#include "../observer/AchievementManager.h"
#include "../observer/Observer.h"

#include <vector>
#include <memory>
#include <map>
#include <functional>

class InputHandler;

// Define the collision callback type
using CollisionCallback = std::function<void(std::shared_ptr<Entity>)>;

class Game
{
public:

	const int spriteWH = 50;
	const float tileScale = 2.0f;
	const float itemScale = 1.0f;

	Game(bool _Debug = false);
	~Game();

	void init(std::vector<std::string> lines);
	void addEntity(std::shared_ptr<Entity> newEntity);

	void buildBoard(size_t width, size_t height);
	void initWindow(size_t width, size_t height);

	void handleInput();
	void update(float elapsed);
	void render(float elapsed);
	Window* getWindow() { return &window; }

	sf::Time getElapsed() const;
	void setFPS(int FPS);
	void togglePause() { paused = !paused; }
	bool isPaused() const { return paused; }

	std::shared_ptr<Player> getPlayer();
	EntityID getIDCounter();
	std::shared_ptr<Entity> getEntity(unsigned int idx);

	template <typename T>
	std::shared_ptr<T> buildEntityAt(const std::string& filename, int col, int row);

	void bigArray(std::vector<std::shared_ptr<System>> _Systems, float _Elapsed);

	void handlePotionCollision(std::shared_ptr<Entity> entity);
	void handleLogCollision(std::shared_ptr<Entity> entity);

	// Observer methods
	void attach(std::unique_ptr<Observer> observer);
	void detach(Observer* observer);
	void notify(const std::string& event);

	std::shared_ptr<Fire> createFireAndNotify() 
	{
		auto fire = player->createFire();
		achievementManager->onNotify("shout");
		return fire;
	}

private:

	Window window;
	bool paused;
	sf::Clock gameClock;
	sf::Time elapsed;

	std::unique_ptr<Board> board;
	std::vector<std::shared_ptr<Entity>> entities;
	EntityID entityCounter;

	std::shared_ptr<Player> player;
	std::unique_ptr<InputHandler> inputHandler;
	std::vector<std::shared_ptr<System>>  logicSystems;
	std::vector<std::shared_ptr<System>>  graphicsSystems;

	// map of collision callbacks
	std::map<EntityType, CollisionCallback> collisionCallbacks;

	// Observer vector
	std::vector<std::unique_ptr<Observer>> observers;
	std::unique_ptr<Observer> observer;
	std::shared_ptr<AchievementManager> achievementManager;
};
