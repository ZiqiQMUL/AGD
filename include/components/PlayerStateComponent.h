#pragma once
#include "../entities/Player.h"
#include "Components.h"

class Game;
class Entity;
class Fire;
class GraphicsComponent;

class LogicComponent :public Component
{
public:
    virtual void update(Game* game, Entity* entity, float elapsed) = 0;
    ComponentID getID()const override { return ComponentID::LOGIC; }
};

class PlayerStateComponent : public LogicComponent
{
public:
    PlayerStateComponent(int maxWood, int shootingCost, float shootCooldownTime) :
        attacking(false),
        shouting(false),
        wood(0),
        shootCooldown(0),
        maxWood(maxWood),
        shootingCost(shootingCost),
        shootCooldownTime(shootCooldownTime)
    {}

    //Getters and setters for the members of this class.
    bool isAttacking() const { return attacking; }
    bool isShouting() const { return shouting; }
    float getShootCooldown() const { return shootCooldown; }
    int getWood() const { return wood; }
    constexpr int getShootingCost() { return shootingCost; }
    constexpr float getShootCooldownTime() { return shootCooldownTime; }
    void setAttacking(bool at) { attacking = at; }
    void setShouting(bool sh) { shouting = sh; }
    void setCooldown(float cd) { shootCooldown = cd; }

    void addWood(int w);
    void update(Game* game, Entity* entity, float elapsed) override;

private:
    bool attacking;
    bool shouting;
    int wood;
    float shootCooldown;

    int maxWood;
    int shootingCost;
    float shootCooldownTime;
};
