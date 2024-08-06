#pragma once

#include <stack>
#include <vector>
#include <string>

class Wizard
{
public:
	Wizard(int health, int agility, int wisdom);

	Wizard() = delete;
	Wizard(const Wizard&) = delete;
	Wizard& operator=(const Wizard&) = delete;

	void SetHealth(int health);
	int GetHealth();
	int GetAgility();
	int GetWisdom();

private:
	int m_health;
	int m_agility;
	int m_wisdom;
};

Wizard* GetWizard(int idxWizard);

class VM
{
public:
	VM();
	void Excute(std::vector<std::string> cmdList);

private:
	int Pop();
	void Push(int value);

	std::stack<int> m_stack;
};