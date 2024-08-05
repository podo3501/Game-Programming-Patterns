#include "SpawnMonster.h"

Ghost::Ghost(int health, int speed) :
	m_health(health),
	m_speed(speed)
{}

std::unique_ptr<Monster> Ghost::Clone()
{
	return std::move(std::make_unique<Ghost>(m_health, m_speed));
}

Spawner::Spawner(Monster* prototype) :
	m_prototype(prototype)
{}

std::unique_ptr<Monster> Spawner::SpawnMonster() 
{
	return m_prototype->Clone();
}