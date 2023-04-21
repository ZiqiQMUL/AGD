#include "../../include/core/Command.h"

void PauseCommand::execute(Game& _Game)
{
	_Game.togglePause();
}