#pragma once

enum Texture
{
	TEXTURE_NONE,
	GRASS_TEXTURE,
	HILL_TEXTURE,
	RIVER_TEXTURE,
};

class Terrain
{
public:
	Terrain(int movementCost, bool isWater, Texture texture);

	Terrain() = delete;
	Terrain(const Terrain&) = delete;
	Terrain& operator=(const Terrain&) = delete;

	int GetMovementCost() const { return m_movementCost; }
	bool IsWater() const { return m_isWater; }
	const Texture& GetTexture() const { return m_texture; }

private:
	int m_movementCost;
	bool m_isWater;
	Texture m_texture;
};

const int WIDTH = 400;
const int HEIGHT = 300;

class World
{
public:
	World();

	World(const World&) = delete;
	World& operator=(const World&) = delete;

	void GenerateTerrain();
	const Terrain& GetTile(int x, int y) const { return *m_tiles[x][y]; }

private:
	Terrain* m_tiles[WIDTH][HEIGHT];

	Terrain m_grassTerrain;
	Terrain m_hillTerrain;
	Terrain m_riverTerrain;
};