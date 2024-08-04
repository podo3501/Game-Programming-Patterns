#include "Undo.h"

int Unit::GetX()
{
	return m_x;
}

int Unit::GetY()
{
	return m_y;
}

void Unit::MoveTo(int x, int y)
{
	m_x = x;
	m_y = y;
}

MoveUnitCommand::MoveUnitCommand(Unit* unit, int x, int y) :
	m_unit(unit), m_x(x), m_y(y),
	m_xBefore(0), m_yBefore(0)
{}

void MoveUnitCommand::Execute()
{
	m_xBefore = m_unit->GetX();
	m_yBefore = m_unit->GetY();
	m_unit->MoveTo(m_x, m_y);
}

void MoveUnitCommand::Undo()
{
	m_unit->MoveTo(m_xBefore, m_yBefore);
}

CommandList::CommandList() :
	m_commandList{}
{}

void CommandList::Move(Unit* unit, int x, int y)
{
	std::unique_ptr<UndoCommand> moveCmd = std::make_unique<MoveUnitCommand>(unit, x, y);
	moveCmd->Execute();

	m_commandList.push(std::move(moveCmd));
}

void CommandList::Undo()
{
	auto cmd = m_commandList.top().get();
	cmd->Undo();

	m_commandList.pop();
}
