#pragma once

#include <memory>
#include <stack>

class Unit
{
public:
	int GetX();
	int GetY();
	void MoveTo(int x, int y);

private:
	int m_x{ 0 };
	int m_y{ 0 };
};

class UndoCommand
{
public:
	virtual ~UndoCommand() {}
	virtual void Execute() = 0;
	virtual void Undo() = 0;
};

class MoveUnitCommand : public UndoCommand
{
public:
	MoveUnitCommand() = delete;
	MoveUnitCommand(const MoveUnitCommand&) = delete;
	MoveUnitCommand& operator=(const MoveUnitCommand&) = delete;

	MoveUnitCommand(Unit* unit, int x, int y);
	virtual void Execute() override;
	virtual void Undo() override;

private:
	Unit* m_unit;
	int m_x;
	int m_y;
	int m_xBefore;
	int m_yBefore;
};

class CommandList
{
public:
	CommandList();
	void Move(Unit* unit, int x, int y);
	void Undo();

private:
	std::stack<std::unique_ptr<UndoCommand>> m_commandList;
};
