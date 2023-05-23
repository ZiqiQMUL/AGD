#pragma once

enum class ComponentID
{
	UNDEFIEND=-1,
	INPUT=0,
	POSITION=1,
	VELOCITY=2,
	COLLIDER=3,
	TTL=4,
	LOGIC=5,
	GRAPHICS=6,
	HEALTH=7,
};

class Component
{
public:
	virtual ComponentID getID() = 0;
};