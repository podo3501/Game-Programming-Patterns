#include "pch.h"
#include "../Command/ChangeInputKey.h"
#include "../Command/Undo.h"
#include "../Flyweight/Terrain.h"
#include "../Observer/Achievement.h"
#include "../Prototype/SpawnMonster.h"
#include "../State/FSM.h"
#include "../Bytecode/VirtualMachine.h"
#include "../TypeObject/Monster.h"
#include "../EventQueue/Audio.h"
#include "../ServiceMediator&Decorator/Locator.h"
#include "../DataLocality/Particle.h"
#include "../DirtyFlag/GraphNode.h"
#include "../ObjectPool/ParticlePool.h"

class GlobalEnv : public ::testing::Environment
{
public:
	GlobalEnv() {}
	~GlobalEnv() {}

	void SetUp()
	{
		//메모리 릭을 잡기 위한 옵션
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

	void TearDown()
	{}
};

//GlobalEnv 클래스의 SetUp을 해주기 위해서.
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

		//지형타일이 공유된다.
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

		//물리엔진에 옵저버를 붙여서 조건이 완수되는지 확인한다.
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

		//프로토타입에 맞춰서 새로운 몬스터를 만든다.
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

namespace EventQueuePattern
{
	TEST(AsyncPlaySound, Test)
	{
		Audio::Init();
		Audio::PlaySound(3, 7);
		PlayMessage msg1 = Audio::Update();
		EXPECT_EQ(msg1.id, 3);
		
		Audio::PlaySound(4, 8);
		Audio::PlaySound(4, 10);
		PlayMessage msg2 = Audio::Update();
		EXPECT_EQ(msg2.id, 4);
		EXPECT_EQ(msg2.volume, 10);
	}
}

namespace ServiceMediatorAndDecorator
{
	using namespace locator;

	TEST(AudioLocator, Test)
	{
		Locator::Initialize();

		std::unique_ptr<locator::Audio> audio = std::make_unique<ConsoleAudio>();
		locator::Audio* addressAudio = audio.get();
		Locator::Provide(audio);
		locator::Audio& serviceAudio = Locator::GetAudio();

		EXPECT_EQ(addressAudio, &serviceAudio);
	}
}

namespace DataLocality
{
	TEST(ParticleSystem, Test)
	{
		ParticleSystem particle;
		particle.Show(0);		//한프레임만 산다.
		particle.Show(1);	
		particle.Update();

		EXPECT_EQ(particle.GetActive(), 1);
	}
}

namespace DirtyFlag
{
	TEST(GraphNode, Test)
	{
		std::unique_ptr<Mesh> meshParent = std::make_unique<Mesh>();
		std::unique_ptr<Mesh> meshChild = std::make_unique<Mesh>();
		std::unique_ptr<GraphNode> nodeParent = std::make_unique<GraphNode>(meshParent.get());
		std::unique_ptr<GraphNode> nodeChild = std::make_unique<GraphNode>(meshChild.get());

		nodeChild->SetTransform(Transform(5));
		nodeParent->Attach(nodeChild.get());
		nodeParent->Render(Transform::Origin(), false);
		
		EXPECT_EQ(nodeParent->GetTransform().GetValue(), 10);
		EXPECT_EQ(nodeChild->GetTransform().GetValue(), 15);
	}
}

namespace ObjectPool
{
	using namespace OP;
	TEST(ObjectPool, Test)
	{
		ParticlePool particlePool;

		particlePool.Create(10, 11, 1, 2, 1);
		particlePool.Create(20, 21, 1, 2, 2);
		particlePool.Animate();

		EXPECT_EQ(particlePool.GetAvailableCount(), 98);
	}
}