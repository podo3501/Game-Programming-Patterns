#pragma once

#include <memory>

class Actor
{
public:
	Actor();

	void Jump();
	void FireGun();
	void SwapWeapon();
};

class Command
{
public:
	virtual ~Command() {}
	virtual void Execute(Actor* actor) = 0;
};

class JumpCommand : public Command
{
public:
	virtual void Execute(Actor* actor) override;
};

class FireCommand : public Command
{
public:
	virtual void Execute(Actor* actor) override;
};

class SwapCommand : public Command
{
public:
	virtual void Execute(Actor* actor) override;
};

class InputHandler
{
public:
	InputHandler();

	Command* handleInput();
	bool isPressed(int n);

private:
	std::unique_ptr<Command> m_btnX;
	std::unique_ptr<Command> m_btnY;
	std::unique_ptr<Command> m_btnZ;
};