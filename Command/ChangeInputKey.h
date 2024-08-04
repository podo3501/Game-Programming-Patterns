#pragma once

#include <memory>
#include <vector>
#include <map>

enum Behavier
{
	BEHAVIER_NONE,
	JUMP,
	FIRE,
	SWAP
};

enum KeyList
{
	KEY_NONE,
	KEY_X,
	KEY_Y,
	KEY_Z
};

class Actor
{
public:
	Actor();

	Behavier Jump();
	Behavier FireGun();
	Behavier SwapWeapon();
};

class Command
{
public:
	virtual ~Command() {}
	virtual Behavier Execute(Actor* actor) = 0;
};

class JumpCommand : public Command
{
public:
	virtual Behavier Execute(Actor* actor) override;
};

class FireCommand : public Command
{
public:
	virtual Behavier Execute(Actor* actor) override;
};

class SwapCommand : public Command
{
public:
	virtual Behavier Execute(Actor* actor) override;
};

class InputHandler
{
public:
	InputHandler();

	Command* handleInput();
	void PressedKey(KeyList key);
	void ChangeKeyInput(KeyList key, Behavier behavier);
	Command* GetCommand(KeyList key);

private:
	bool isPressed(KeyList key);

private:
	std::map<Behavier, std::unique_ptr<Command>> m_behavierCommand;
	std::map<KeyList, Behavier> m_keyList;

	KeyList m_pressedKey;

	std::unique_ptr<Command> m_btnX;
	std::unique_ptr<Command> m_btnY;
	std::unique_ptr<Command> m_btnZ;
};