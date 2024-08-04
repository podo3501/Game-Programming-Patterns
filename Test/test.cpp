#include "pch.h"
#include "../Command/ChangeInputKey.h"
#include <string>

TEST(ChangeInputKey, Change) 
{
	std::unique_ptr<Actor> actor = std::make_unique<Actor>();
	std::unique_ptr<InputHandler> inputHandler = std::make_unique<InputHandler>();

	inputHandler->ChangeKeyInput(KEY_Y, JUMP);
	inputHandler->PressedKey(KEY_Y);

	Command* cmd = inputHandler->handleInput();
	if (cmd)
		EXPECT_EQ(cmd->Execute(actor.get()), JUMP);

	//원래 JUMP가 등록되었던 KEY_X는 nullptr 처리되었다.
	EXPECT_EQ(inputHandler->GetCommand(KEY_X), nullptr);
}