#pragma once

#include "../Entities/Player.h"
#include "../core/Game.h"

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(Game& game) = 0;
protected:
    static VelocityComponent* getVelocityComponent(Game& game);
    static PlayerStateComponent* getPlayerStateComponent(Game& game);
};

class PauseCommand : public Command
{
public:
    void execute(Game& game) override;
};

class MoveCommand : public Command
{
protected:
    virtual void move(VelocityComponent* velocityComp) = 0;
};

class MoveRightCommand : public MoveCommand
{
public:
    void execute(Game& game) override;
    void move(VelocityComponent* velocityComp) override;
};

class MoveLeftCommand : public MoveCommand
{
public:
    void execute(Game& game) override;
    void move(VelocityComponent* velocityComp) override;
};

class MoveUpCommand : public MoveCommand
{
public:
    void execute(Game& game) override;
    void move(VelocityComponent* velocityComp) override;
};

class MoveDownCommand : public MoveCommand
{
public:
    void execute(Game& game) override;
    void move(VelocityComponent* velocityComp) override;
};

class ActionCommand : public Command
{
protected:
    virtual void action(PlayerStateComponent* playerStateComp) = 0;
};

class AttackCommand :public ActionCommand
{
public:
    void execute(Game& game) override;
    void action(PlayerStateComponent* playerStateComp) override;
};

class ShoutCommand :public ActionCommand
{
public:
    void execute(Game& game) override;
    void action(PlayerStateComponent* playerStateComp) override;
};