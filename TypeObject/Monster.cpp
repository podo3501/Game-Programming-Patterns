#include "Monster.h"
#include <fstream>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <codecvt>
#include <Windows.h>
#include "./include/nlohmann/json.hpp"

using namespace TO; 

Breed::Breed(Breed* parent, int health, const std::wstring& attack) :
	m_parent{ parent },
	m_health{ health },
	m_attack{ attack }
{
	if (parent == nullptr)
		return;
	
	if (m_health == 0)
		m_health = parent->GetHealth();
	if (m_attack.empty())
		m_attack = parent->GetAttack();
}

std::unique_ptr<Monster> Breed::NewMonster()
{
	//private 생성자에 스마트 포인터로 접근할 경우에는 new로 생성해준다.
	std::unique_ptr<Monster> monster(new Monster(this));
	return std::move(monster);
}

int Breed::GetHealth() { return m_health; }
std::wstring Breed::GetAttack() { return m_attack; }

//////////////////////////////////////////////////////////////////////

Monster::Monster(Breed* breed) :
	m_health{ breed->GetHealth() },
	m_breed{ breed }
{}

std::wstring Monster::GetAttack() { return m_breed->GetAttack(); }
int Monster::GetHealth() { return m_health; }

//////////////////////////////////////////////////////////////////////

std::wstring UTF8ToWideString(const std::string& utf8)
{
	wchar_t strUnicode[256] = { 0, };
	int strLen = static_cast<int>(strlen(utf8.c_str()));
	int nLen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), strLen, NULL, NULL);
	MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), strLen, strUnicode, nLen);

	return strUnicode;
}

using json = nlohmann::json;

BreedType GetBreedType(const std::string& strBreed)
{
	if (strBreed == "Troll") return Troll;
	if (strBreed == "TrollArcher") return TrollArcher;
	if (strBreed == "TrollMage") return TrollMage;

	return None;
}

Breed* MonsterManager::FindBreed(BreedType type)
{
	auto find = m_breedList.find(type);
	if (find == m_breedList.end())
		return nullptr;

	return find->second.get();
}

void MonsterManager::CreateBreed(const std::wstring& filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
		return;

	json dataList = json::parse(file);
	for(auto& [breed, properties] : dataList.items())
	{
		BreedType breedType = GetBreedType(breed);
		if(FindBreed(breedType) != nullptr)
			continue;		

		Breed* parentBreed = nullptr;
		int health = 0;
		std::wstring attack{};

		for (auto& [property, data] : properties.items())
		{
			if (property == "Parent")
				parentBreed = FindBreed(GetBreedType(data));
			if (property == "Health")
				health = data;
			if (property == "Attack")
			{
				std::string strAttack = data.template get<std::string>();
				attack = UTF8ToWideString(strAttack);
			}
		}

		m_breedList.insert(std::make_pair(breedType, std::make_unique<Breed>(parentBreed, health, attack)));
	}
}

std::unique_ptr<Monster> MonsterManager::MakeMonster(BreedType type)
{
	auto find = m_breedList.find(type);
	if (find == m_breedList.end())
		return nullptr;

	return find->second->NewMonster();
}
