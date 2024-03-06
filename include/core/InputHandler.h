#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "../../include/core/Command.h"

class Command;

enum class InputMode { ASDW, CursorKeys }; //Tuning the Command pattern (15%)

class KeyboardInputHandler
{
public:
    KeyboardInputHandler();

    void handleEvent(sf::Event event);

    bool isEscapePressed() const;
    bool isEscapeReleased() const;
    void setEscapeReleased(bool value);
    void setEscapePressed(bool value);

private:
    bool escapePressed;
    bool escapeReleased;
};

class InputHandler
{
public:
    InputHandler();
    InputHandler(Game* game);
    std::shared_ptr<Command> handleInput();

private:
    std::shared_ptr<Command> pauseCommand;
    KeyboardInputHandler keyboardInputHandler;
    bool paused;
    Game* game;
};


class PlayerInputHandler
{
public:
    PlayerInputHandler();

    std::vector<std::shared_ptr<Command>> handleInput();

private:
    std::vector<std::shared_ptr<Command>> commands;

    std::shared_ptr<Command> moveRightCommand;
    std::shared_ptr<Command> moveLeftCommand;
    std::shared_ptr<Command> moveUpCommand;
    std::shared_ptr<Command> moveDownCommand;

    std::shared_ptr<Command> attackCommand;
    std::shared_ptr<Command> shoutCommand;

    InputMode inputMode = InputMode::ASDW;//Tuning the Command pattern
};