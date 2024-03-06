#include "../core/Game.h"
#include "../entities/Fire.h"
#include "../entities/StaticEntities.h"
#include "../service/Locator.h"
#include <iostream>

// III.F Add the initialization (to 0) of the entity counter to the initalizers list of this constructor
Game::Game(bool _Debug) : paused(false), entityCounter(0)//III.F
{
	inputHandler = std::make_unique<InputHandler>(this);

	logicSystems.emplace_back(std::make_shared<TTLSystem>());
	logicSystems.emplace_back(std::make_shared<InputSystem>());
	logicSystems.emplace_back(std::make_shared<MovementSystem>());
	logicSystems.emplace_back(std::make_shared<GameplaySystem>());
	logicSystems.emplace_back(std::make_shared<ColliderSystem>());

	graphicsSystems.emplace_back(std::make_shared<GraphicsSystem>());
	if (_Debug)graphicsSystems.emplace_back(std::make_shared<PrintDebugSystem>());

	// Initialize collisionCallbacks
	collisionCallbacks[EntityType::POTION] = [this](std::shared_ptr<Entity> entity) 
	{
		handlePotionCollision(entity);
	};

	collisionCallbacks[EntityType::LOG] = [this](std::shared_ptr<Entity> entity) 
	{
		handleLogCollision(entity);
	};

	collisionCallbacks[EntityType::POTION] = std::bind(&Game::handlePotionCollision, this, std::placeholders::_1);
	collisionCallbacks[EntityType::LOG] = std::bind(&Game::handleLogCollision, this, std::placeholders::_1);
	observer = std::make_unique<AchievementManager>();
}


//¨C Collisions (15%)
void Game::handlePotionCollision(std::shared_ptr<Entity> entity)
{
	auto potion = dynamic_cast<Potion*>(entity.get());
	auto value = potion->getHealth();
	dynamic_cast<HealthComponent*>(player->getComponent(ComponentID::HEALTH))->changeHealth(value);
	std::cout << "Restore " << value << " Health, now Health=" << dynamic_cast<PlayerStateComponent*>(player->getComponent(ComponentID::LOGIC))->getWood() << std::endl;
	potion->deleteEntity();
	notify("potion");
	Audio& service = Locator::getAudio();
	service.playAudio(AUDIO_TYPE::POTION);
}

void Game::handleLogCollision(std::shared_ptr<Entity> entity)
{
	auto graphicsComp = dynamic_cast<GraphicsComponent*>(player->getComponent(ComponentID::GRAPHICS));
	if (dynamic_cast<PlayerStateComponent*>(player->getComponent(ComponentID::LOGIC))->isAttacking()
		&& graphicsComp->getCurrentAnim()->getName() == "Attack"
		&& graphicsComp->getCurrentAnim()->isInAction())
	{
		auto log = dynamic_cast<Log*>(entity.get());
		auto value = log->getWood();
		player->addWood(value);
		std::cout << "Get " << value << " Wood, now Wood=" << dynamic_cast<PlayerStateComponent*>(player->getComponent(ComponentID::LOGIC))->getWood() << std::endl;
		log->deleteEntity();

		Audio& service = Locator::getAudio();
		service.playAudio(AUDIO_TYPE::AXE);
	}
}

void Game::attach(std::unique_ptr<Observer> observer)
{
	this->observer = std::move(observer);
}

void Game::detach(Observer* observer)
{
}

void Game::notify(const std::string& event)
{
	if (observer)
	{
		observer->onNotify(event);
	}
}

//¨C Collisions(15 %)

Game::~Game()
{
}

template <typename T>
std::shared_ptr<T> Game::buildEntityAt(const std::string& filename, int col, int row)
{
	auto ent = std::make_shared<T>();
	float x = col * spriteWH * tileScale;
	float y = row * spriteWH * tileScale;
	float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;

	dynamic_cast<PositionComponent*>(ent->getComponent(ComponentID::POSITION))->setPosition(x + cntrFactor, y + cntrFactor);
	//ent->setVelocity({ 0.0f, 0.0f });
	ent->init(filename, std::make_shared<SpriteGraphicsComponent>(itemScale));
	
	return ent;
}

void Game::buildBoard(size_t width, size_t height)
{
	board = std::make_unique<Board>(width, height);//II.B
}

void Game::initWindow(size_t width, size_t height)
{
	int wdt = static_cast<int>(width * spriteWH * tileScale);
	int hgt = static_cast<int>(height * spriteWH * tileScale);
	window.setSize(sf::Vector2u(wdt, hgt));
	window.redraw();
}

void Game::init(std::vector<std::string> lines)
{
	// Make sure that the vector of lines is not emtpy. h is the number of lines (height of the level)
	size_t h = lines.size() - 1;
	if (h == 0)
		throw std::exception("No data in level file");
	size_t w = -1;//1C 

	// Load the font for the window and set its title
	window.loadFont("font/AmaticSC-Regular.ttf");
	window.setTitle("Mini-Game");
	
	auto it = lines.cbegin();
	int row = 0;
	while (it != lines.cend())
	{
		int col = 0;

		// First iteration: we determine the width of the level (w) by the number of symbols in the first line.
		if(w == -1)
		{
			//The size of the window must be equal to the number of tiles it has, factoring their dimensions.
			w = it->size();
			buildBoard(w, h);
			initWindow(w, h);		
		}
		
		std::string::const_iterator is = it->cbegin();
		while (is != it->cend())
		{
			switch (*is)
			{
			case '.':
			{
				board->addTile(col, row, tileScale, TileType::CORRIDOR);//II.C (1/5)

				break;
			}
			case 'w':
			{
				// II.C (2/5) Use the function addTile from Board to add a WALL tile to this position.
				board->addTile(col, row, tileScale, TileType::WALL);//II.C (2/5)

				break;
			}
			case 'x':
			{
				auto entLog = buildEntityAt<Log>("img/log.png", col, row);
				addEntity(entLog);//III.A

				// II.C (3/5) Use the function addTile from Board to add a CORRIDOR tile to this position.
				board->addTile(col, row, tileScale, TileType::CORRIDOR);//II.C (3/5)

				break;
			}
			case 'p':
			{
		
				auto entPotion = buildEntityAt<Potion>("img/potion.png", col, row);
				addEntity(entPotion);//III.B
				board->addTile(col, row, tileScale, TileType::CORRIDOR);//II.C (4/5)

				break;
			}
			case '*':
				{
				auto playerPtr = std::make_shared<Player>();//IV.B (1/4)
				player = playerPtr;
				player->init("img/DwarfSpriteSheet_data.txt", std::make_shared<SpriteSheetGraphicsComponent>());//IV.B (2/4)
				player->positionSprite(row, col, spriteWH, tileScale);//IV.B (3/4)

				// IV.B (4/4): Call our function to add an entity to a game passing the player that has just been created.
				addEntity(player);//IV.B (4/4)
				board->addTile(col, row, tileScale, TileType::CORRIDOR);//II.C (5/5)

				break;
				}
			}

			col++; is++;
		}
		row++; it++;
	}
}

void Game::addEntity(std::shared_ptr<Entity> newEntity)
{
	entityCounter++; 
	newEntity->setID(entityCounter); 
	entities.push_back(newEntity); // III.I
}

void Game::handleInput()
{
	auto cmd = inputHandler->handleInput();
	if (cmd != nullptr)cmd->execute(*this);
}

void Game::update(float elapsed)
{
	if (!paused)
	{
		bigArray(logicSystems, elapsed);

		for (auto& entity : entities)
		{
			if (entity == player)continue;

			if (player->collidesWith(entity))//player box is bigger
			{
				auto entityType = entity->getEntityType();
				auto callbackIt = collisionCallbacks.find(entityType);
				if (callbackIt != collisionCallbacks.end())
				{
					// Call the collision callback for this entity type
					callbackIt->second(entity);
				}
			}
		}

		for (auto it3 = entities.begin(); it3 != entities.end();)
		{
			if ((*it3)->isDeleted())
			{
				it3 = entities.erase(it3);
			}
			else
				++it3;
		}
	}

	//Update the window for refreshing the graphicsComp (leave this OUTSIDE the !paused block)
	window.update();
}

void Game::render(float elapsed)
{
	//Empty the screen
	window.beginDraw();

	// II.D Call the draw method of the board object passing a pointer to the window.
	board->draw(&window);//II.D

	bigArray(graphicsSystems, elapsed);

	//Draw FPS
	window.drawGUI(*this);

	//Close up for this frame.
	window.endDraw();
}


sf::Time Game::getElapsed() const { return gameClock.getElapsedTime(); }


void Game::setFPS(int FPS)
{
	std::string text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}

// III.G Return the current ID counter.
EntityID Game::getIDCounter()
{
	return entityCounter;//III.G
}

std::shared_ptr<Entity> Game::getEntity(unsigned int index)
{
	if (index >= 0 && index < entities.size())
	{
		return entities[index]; // Return the pointer to the entity at the specified index
	}
	else 
	{
		return nullptr;
	}//III.H
}

std::shared_ptr<Player> Game::getPlayer()
{
	return player;
}

void Game::bigArray(std::vector<std::shared_ptr<System>> systems, float elapsedTime)
{
	auto system_it = systems.begin();

	while (system_it != systems.end()) 
	{
		auto entity_it = entities.begin();
		while (entity_it != entities.end()) {

			if (!(*entity_it)->isDeleted() && (*system_it)->validate(*entity_it)) {
				(*system_it)->update(this, *entity_it, elapsedTime);
			}
			++entity_it;
		}
		++system_it;
	}
}