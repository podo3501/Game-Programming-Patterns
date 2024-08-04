#include "pch.h"
#include <string>
#include "../Command/ChangeInputKey.h"
#include "../Command/Undo.h"

namespace CommandPattern
{
	TEST(ChangeInputKey, Test)
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

	TEST(Undo, Test)
	{
		auto unit = std::make_unique<Unit>();
		int xBefore = unit->GetX();
		int yBefore = unit->GetY();

		int xMoveFirst = 10;
		int yMoveFirst = 11;

		int xMoveSecond = 20;
		int yMoveSecond = 21;

		CommandList cmdList;
		cmdList.Move(unit.get(), xMoveFirst, yMoveFirst);
		EXPECT_EQ(unit->GetX(), xMoveFirst);
		EXPECT_EQ(unit->GetY(), yMoveFirst);

		cmdList.Move(unit.get(), xMoveSecond, yMoveSecond);
		EXPECT_EQ(unit->GetX(), xMoveSecond);
		EXPECT_EQ(unit->GetY(), yMoveSecond);

		cmdList.Undo();
		EXPECT_EQ(unit->GetX(), xMoveFirst);
		EXPECT_EQ(unit->GetY(), yMoveFirst);

		cmdList.Undo();
		EXPECT_EQ(unit->GetX(), xBefore);
		EXPECT_EQ(unit->GetY(), yBefore);
	}
}
