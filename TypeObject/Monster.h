#pragma once

#include <string>
#include <memory>
#include <map>

namespace TO
{
	class Monster;

	class Breed
	{
	public:
		Breed(Breed* parent, int health, const std::wstring& attack);

		Breed() = delete;
		Breed(const Breed&) = delete;
		Breed& operator=(const Breed&) = delete;

		std::unique_ptr<Monster> NewMonster();

		int GetHealth();
		std::wstring GetAttack();

	private:
		Breed* m_parent;
		int m_health;
		std::wstring m_attack;
	};

	class Monster
	{
		friend class Breed;

	public:
		Monster() = delete;
		Monster(const Monster&) = delete;
		Monster& operator=(const Monster&) = delete;

		std::wstring GetAttack();
		int GetHealth();

	private:
		Monster(Breed* breed);

		int m_health;
		Breed* m_breed;
	};

	enum BreedType
	{
		None,
		Troll,
		TrollArcher,
		TrollMage
	};

	class MonsterManager
	{
	public:
		void CreateBreed(const std::wstring& filename);
		std::unique_ptr<Monster> MakeMonster(BreedType type);

	private:
		Breed* FindBreed(BreedType type);

		std::map<BreedType, std::unique_ptr<Breed>> m_breedList;
	};
}