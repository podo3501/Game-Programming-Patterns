#include "ChangeInputKey.h"
#include <ranges>
#include <algorithm>

Actor::Actor()
{}
Behavier Actor::Jump() 
{
	return JUMP;
}

Behavier Actor::FireGun() 
{
	return FIRE;
}

Behavier Actor::SwapWeapon() 
{
	return SWAP;
}

Behavier JumpCommand::Execute(Actor* actor)
{
	return actor->Jump();
}

Behavier FireCommand::Execute(Actor* actor)
{
	return actor->FireGun();
}

Behavier SwapCommand::Execute(Actor* actor)
{
	return actor->SwapWeapon();
}

InputHandler::InputHandler() :
	m_pressedKey{ KEY_NONE },
	m_btnX{ std::make_unique<JumpCommand>() },
	m_btnY{ std::make_unique<FireCommand>() },
	m_btnZ{ std::make_unique<SwapCommand>() }
{
	m_behavierCommand.insert(std::make_pair(JUMP, std::make_unique<JumpCommand>()));
	m_behavierCommand.insert(std::make_pair(FIRE, std::make_unique<FireCommand>()));
	m_behavierCommand.insert(std::make_pair(SWAP, std::make_unique<SwapCommand>()));

	m_keyList.insert(std::make_pair(KEY_X, JUMP));
	m_keyList.insert(std::make_pair(KEY_Y, FIRE));
	m_keyList.insert(std::make_pair(KEY_Z, SWAP));
}

void InputHandler::ChangeKeyInput(KeyList key, Behavier behavier)
{
	auto find = m_keyList.find(key);
	if (find == std::cend(m_keyList))
		return;

	std::ranges::for_each(m_keyList, [behavier](auto& key) {
		if (key.second != behavier)
			return;
		key.second = BEHAVIER_NONE;
		}); 

	find->second = behavier;
}

void InputHandler::PressedKey(KeyList key)
{
	m_pressedKey = key;
}

bool InputHandler::isPressed(KeyList key)
{
	return (m_pressedKey == key);
}

Command* InputHandler::GetCommand(KeyList key)
{
	auto find = m_keyList.find(key);
	if (find == std::cend(m_keyList))
		return nullptr;

	auto cmd = m_behavierCommand.find(find->second);
	if (cmd == std::cend(m_behavierCommand))
		return nullptr;

	return cmd->second.get();
}

Command* InputHandler::handleInput()
{
	return GetCommand(m_pressedKey);
}