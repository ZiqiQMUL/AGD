#include "../core/Game.h"
#include "../core/Command.h"

void PauseCommand::execute(Game& game)
{
    game.togglePause();
}
