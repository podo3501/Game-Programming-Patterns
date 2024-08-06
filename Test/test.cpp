#include "pch.h"
#include "../Command/ChangeInputKey.h"
#include "../Command/Undo.h"
#include "../Flyweight/Terrain.h"
#include "../Observer/Achievement.h"
#include "../Prototype/SpawnMonster.h"
#include "../State/FSM.h"
#include "../Bytecode/VirtualMachine.h"
#include "../TypeObject/Monster.h"

class GlobalEnv : public ::testing::Environment
{
public:
	GlobalEnv() {}
	~GlobalEnv() {}

	void SetUp()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

	void TearDown()
	{}
};

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	::testing::AddGlobalTestEnvironment(new GlobalEnv);

	return RUN_ALL_TESTS();
}

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

namespace FlyweightPattern
{
	TEST(Terrain, Test)
	{
		World world;
		world.GenerateTerrain();

		auto movementCost = world.GetTile(2, 3).GetMovementCost();
		EXPECT_GE(movementCost, 0);
	}
}

namespace ObserverPattern
{
	TEST(Achievement, Test)
	{
		Entity entity;
		Physics physics;
		Achievements achievements;

		physics.AddObserver(&achievements);

		physics.UpdateEntity(entity);

		EXPECT_EQ(achievements.IsFell(), true);
	}
}

namespace PrototypePattern
{
	TEST(SpawnMonster, Test)
	{
		std::unique_ptr<Monster> ghostPrototype = std::make_unique<Ghost>(15, 3);
		std::unique_ptr<Spawner> ghostSpawner = std::make_unique<Spawner>(ghostPrototype.get());
		EXPECT_EQ(ghostPrototype->GetHealth(), 15);

		std::unique_ptr<Monster> ghost = ghostSpawner->SpawnMonster();
		EXPECT_EQ(ghost->GetHealth(), 15);
	}
}

namespace StatePattern
{
	TEST(FiniteStateMachine, Test)
	{
		Heroine heroine;
		EXPECT_EQ(heroine.GetGraph(), IMAGE_STAND);

		heroine.HandleInput(PRESS_DOWN);
		EXPECT_EQ(heroine.GetGraph(), IMAGE_DUCKING);
	}
}

namespace BytecodePattern
{
	TEST(VirtualMachine, Test)
	{
		VM vm;
		std::vector<std::string> cmdList;
		cmdList.emplace_back("LITERAL 0");
		cmdList.emplace_back("LITERAL 0");
		cmdList.emplace_back("GET_HEALTH");
		cmdList.emplace_back("LITERAL 0");
		cmdList.emplace_back("GET_AGILITY");
		cmdList.emplace_back("LITERAL 0");
		cmdList.emplace_back("GET_WISDOM");
		cmdList.emplace_back("ADD");
		cmdList.emplace_back("LITERAL 2");
		cmdList.emplace_back("DIVIDE");
		cmdList.emplace_back("ADD");
		cmdList.emplace_back("SET_HEALTH");
		vm.Excute(cmdList);

		auto wizard = GetWizard(0);
		EXPECT_EQ(wizard->GetHealth(), 54);
	}
}

namespace TypeObjectPattern
{
	using namespace TO;
	TEST(MonsterBreed, Test)
	{
		MonsterManager manager;
		manager.CreateBreed(L"./Test/monster.json");

		std::unique_ptr<TO::Monster> trollArcher = manager.MakeMonster(TrollArcher);
		EXPECT_EQ(trollArcher->GetAttack(), L"트롤 궁수가 활을 쏩니다!");
		EXPECT_EQ(trollArcher->GetHealth(), 25);
	}
}