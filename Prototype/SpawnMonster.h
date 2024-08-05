#pragma once

#include <memory>
#include <functional>

class Monster
{
public:
	virtual ~Monster() {}
	virtual std::unique_ptr<Monster> Clone() = 0;
	virtual int GetHealth() = 0;
};

class Ghost : public Monster
{
public:
	Ghost(int health, int speed);

	Ghost() = delete;
	Ghost(const Ghost&) = delete;
	Ghost& operator=(const Ghost&) = delete;

	virtual std::unique_ptr<Monster> Clone();

	virtual int GetHealth() override { return m_health; }

private:
	int m_health{ 0 };
	int m_speed{ 0 };
};

class Spawner
{
public:
	Spawner(Monster* prototype);
	std::unique_ptr<Monster> SpawnMonster();

private:
	Monster* m_prototype;
};