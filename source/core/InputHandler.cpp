#include "../core/InputHandler.h"
#include "../core/Game.h"
#include "../core/Command.h"

KeyboardInputHandler::KeyboardInputHandler() : escapePressed(false), escapeReleased(false)
{

}

bool KeyboardInputHandler::isEscapePressed() const
{
    return escapePressed;
}

bool KeyboardInputHandler::isEscapeReleased() const
{
    return escapeReleased;
}

void KeyboardInputHandler::setEscapePressed(bool value)
{
    escapeReleased = value;
}

void KeyboardInputHandler::setEscapeReleased(bool value)
{
    escapeReleased = value;
}


InputHandler::InputHandler() : paused(false)
{
    pauseCommand = std::make_shared<PauseCommand>();
}

InputHandler::InputHandler(Game* game) : game(game), paused(false), keyboardInputHandler()
{
    pauseCommand = std::make_shared<PauseCommand>();
}


std::shared_ptr<Command> InputHandler::handleInput()
{
    std::shared_ptr<Command> command;

    static bool prevEscapePressed = false; // last Key pressed
    bool isEscapePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    if (isEscapePressed != prevEscapePressed) // when key changed
    {
        if (isEscapePressed)
        {
            paused = true;
            command = pauseCommand;
        }
        else
        {
            paused = false;
        }
    }
    keyboardInputHandler.setEscapePressed(isEscapePressed);
    prevEscapePressed = isEscapePressed;

    return command;
}

void KeyboardInputHandler::handleEvent(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Escape && !escapePressed)
        {
            escapePressed = true;
        }
        break;

    case sf::Event::KeyReleased:
        if (event.key.code == sf::Keyboard::Escape && !escapeReleased)
        {
            escapePressed = false;
            escapeReleased = true;
        }
        break;

    default:
        break;
    }
}


PlayerInputHandler::PlayerInputHandler()
{
    moveRightCommand = std::make_shared<MoveRightCommand>();
    moveLeftCommand = std::make_shared<MoveLeftCommand>();
    moveUpCommand = std::make_shared<MoveUpCommand>();
    moveDownCommand = std::make_shared<MoveDownCommand>();

    attackCommand = std::make_shared<AttackCommand>();
    shoutCommand = std::make_shared<ShoutCommand>();
}

// Tuning the Command pattern (15%)
std::vector<std::shared_ptr<Command>> PlayerInputHandler::handleInput()
{
    commands.clear();

    static bool prevEnterPressed = false;
    bool isEnterPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
    if (isEnterPressed && !prevEnterPressed) // only switch if key was just pressed
    {
        inputMode = (inputMode == InputMode::ASDW) ? InputMode::CursorKeys : InputMode::ASDW;
    }
    prevEnterPressed = isEnterPressed;

    if (inputMode == InputMode::ASDW)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            commands.push_back(moveRightCommand);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            commands.push_back(moveLeftCommand);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            commands.push_back(moveUpCommand);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            commands.push_back(moveDownCommand);
        }
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            commands.push_back(moveRightCommand);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            commands.push_back(moveLeftCommand);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            commands.push_back(moveUpCommand);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            commands.push_back(moveDownCommand);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        commands.push_back(attackCommand);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        commands.push_back(shoutCommand);
    }

    return commands;
}

