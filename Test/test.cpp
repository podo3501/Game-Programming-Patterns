#include "pch.h"
#include "../Command/ChangeInputKey.h"
#include <string>

TEST(ChangeInputKey, Change) 
{
	std::unique_ptr<Actor> actor = std::make_unique<Actor>();
	std::unique_ptr<InputHandler> inputHandler = std::make_unique<InputHandler>();

	Command* cmd = inputHandler->handleInput();
	if (cmd)
	{
		cmd->Execute(actor.get());
	}
}