#include "Terrain.h"
#include <random>
#include <ranges>

Terrain::Terrain(int movementCost, bool isWater, Texture texture) :
	m_movementCost{ movementCost },
	m_isWater{ isWater },
	m_texture{ texture }
{}

World::World() :
	m_grassTerrain(1, false, GRASS_TEXTURE),
	m_hillTerrain(3, false, HILL_TEXTURE),
	m_riverTerrain(2, true, RIVER_TEXTURE)
{}

int Random(int start, int end)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(start, end);

	return dist(mt);
}

void World::GenerateTerrain()
{
	for (auto x : std::views::iota(0, WIDTH))
	{
		for (auto y : std::views::iota(0, HEIGHT))
		{
			if (Random(0, 9) == 0)
				m_tiles[x][y] = &m_hillTerrain;
			else
				m_tiles[x][y] = &m_grassTerrain;
		}
	}

	int x = Random(0, WIDTH);
	for (auto y : std::views::iota(0, HEIGHT))
	{
		m_tiles[x][y] = &m_riverTerrain;
	}
}