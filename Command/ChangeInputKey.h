#pragma once

#include <memory>

class Command
{
public:
	virtual ~Command() {}
	virtual void Execute() = 0;
};

class JumpCommand : public Command
{
public:
	virtual void Execute() override;
};

class FireCommand : public Command
{
public:
	virtual void Execute() override;
};

class SwapCommand : public Command
{
public:
	virtual void Execute() override;
};

class InputHandler
{
public:
	InputHandler();

	void handleInput();
	bool isPressed(int n);

private:
	std::unique_ptr<Command> m_btnX;
	std::unique_ptr<Command> m_btnY;
	std::unique_ptr<Command> m_btnZ;
};