#pragma once
#include <array>
#include <functional>
#include <list>

namespace SP
{
	class Grid;

	class Unit
	{
		friend class Grid;

	public:
		Unit(Grid* grid, double x, double y);
		void Move(double x, double y);

	private:
		double m_x, m_y;
		Grid* m_grid;
	};

	class Grid
	{
	public:
		Grid();
		void Add(Unit* unit);
		void HandleMelee();
		void Move(Unit* unit, double x, double y);
		int GetAttackCheckCount() { return m_attackCheckCount; }

	private:
		void Each(std::function<void(std::list<Unit*>&)> action);
		void Add(Unit* unit, int cellX, int cellY);
		void Delete(Unit* unit, int cellX, int cellY);
		void HandleAttack(Unit* unit, Unit* other);
		void HandleCell(std::list<Unit*>& unitList);
		decltype(auto) GetCellPosition(double x, double y);

		static constexpr int NUM_CELLS = 10;
		static constexpr int CELL_SIZE = 20;

		std::array<std::array<std::list<Unit*>, NUM_CELLS>, NUM_CELLS> m_cells;
		int m_attackCheckCount;
	};
}