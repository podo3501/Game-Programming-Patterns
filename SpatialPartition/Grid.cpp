#include "Grid.h"
#include <tuple>

using namespace SP;

Unit::Unit(Grid* grid, double x, double y) :
	m_grid{ grid },
	m_x{ x }, m_y{ y }
{
	m_grid->Add(this);
}

void Unit::Move(double x, double y)
{
	m_grid->Move(this, x, y);
}

////////////////////////////////////////////////////////////////

Grid::Grid() :
	m_attackCheckCount{ 0 }
{
	Each([](std::list<Unit*>& unit) { unit.clear(); });
}

void Grid::Each(std::function<void(std::list<Unit*>&)> action)
{
	for (auto& row : m_cells)
		for (auto& cell : row)
			action(cell);
}

decltype(auto) Grid::GetCellPosition(double x, double y)
{
	return std::make_tuple(static_cast<int>(x / CELL_SIZE), static_cast<int>(y / CELL_SIZE));
}

void Grid::Add(Unit* unit)
{
	auto cellxy = GetCellPosition(unit->m_x, unit->m_y);

	Add(unit, std::get<0>(cellxy), std::get<1>(cellxy));
}

void Grid::Delete(Unit* unit, int cellX, int cellY)
{
	auto& unitList = m_cells[cellX][cellY];
	unitList.remove(unit);
}

void Grid::Add(Unit* unit, int cellX, int cellY)
{
	auto& unitList = m_cells[cellX][cellY];
	unitList.emplace_front(unit);
}

void Grid::HandleMelee()
{
	Each([this](std::list<Unit*>& unit) { HandleCell(unit); });
}

void Grid::HandleAttack(Unit* unit, Unit* other)
{
	return;
}

void Grid::HandleCell(std::list<Unit*>& unitList)
{
	if (unitList.size() < 2) return;

	for (auto iter = unitList.begin(); iter != std::prev(unitList.end(), 1); ++iter)
	{
		Unit* unit = *iter;
		for (auto otherIter = std::next(iter, 1); otherIter != unitList.end(); ++otherIter)
		{
			Unit* other = *otherIter;
			if (unit->m_x == other->m_x && unit->m_y == other->m_y)
				HandleAttack(unit, other);
			m_attackCheckCount++;
		}
	}
}

void Grid::Move(Unit* unit, double x, double y)
{
	auto oldPos = GetCellPosition(unit->m_x, unit->m_y);
	auto newPos = GetCellPosition(x, y);

	unit->m_x = x;
	unit->m_y = y;

	if (oldPos == newPos) return;

	Delete(unit, std::get<0>(oldPos), std::get<1>(oldPos));
	Add(unit, std::get<0>(newPos), std::get<1>(newPos));
}