#pragma once
#include "../graphics/Window.h"
#include "../graphics/SpriteSheet.h"
#include "../utils/Rectangle.h"
#include "../utils/Bitmask.h"
#include "../components/Components.h"
#include <map>

using EntityID = unsigned int;
enum class EntityType
{
	UNDEFINED = -1,
	PLAYER = 0,
	POTION = 1,
	LOG = 2,
	FIRE = 3
};

class Game; //forward declaration
class PositionComponent;
class GraphicsComponent;
class ColliderComponent;
class InputComponent;
class VelocityComponent;
class LogicComponent;
class TTLComponent;

class Entity
{
public:

	//Constructors and Desctrutors
	Entity();
	Entity(EntityType et);
	~Entity();

	//Init and update functions
	virtual void init(const std::string& textureFile, std::shared_ptr<GraphicsComponent> gc);

	//Getters and Setters
	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }
	const sf::Vector2f& getSpriteScale() const;
	sf::Vector2i getTextureSize() const;
	EntityType getEntityType() const { return type; }
	
	// X.C  Add two helper functions. One that returns the value of the deleted flag, another one that 
	//      "deletes" the entity by setting this flag to true. (Q: one of this functions should be "const", which one?).
	bool isDeleted()const { return deleted; }
	void deleteEntity() { deleted = true; }

	const Bitmask& getCompoentSet()const { return compSet; }

	bool hasComponent(Bitmask _Mask);

	const Component* getComponent(ComponentID _ID)const;
	 Component* getComponent(ComponentID _ID);
	void addComponent(std::shared_ptr<Component> _CompPtr);


protected:

	EntityType type;
	EntityID id;

	std::map<ComponentID, std::shared_ptr<Component>> components;

	// X.A Add a bool member variable "deleted" to this class.
	bool deleted;

	Bitmask compSet;
};