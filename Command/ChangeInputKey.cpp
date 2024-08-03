#include "ChangeInputKey.h"

Actor::Actor()
{}
void Actor::Jump() 
{};
void Actor::FireGun() 
{};
void Actor::SwapWeapon() 
{};

void JumpCommand::Execute(Actor* actor)
{
	actor->Jump();
}

void FireCommand::Execute(Actor* actor)
{
	actor->FireGun();
}

void SwapCommand::Execute(Actor* actor)
{
	actor->SwapWeapon();
}

InputHandler::InputHandler() :
	m_btnX{ std::make_unique<JumpCommand>() },
	m_btnY{ std::make_unique<FireCommand>() },
	m_btnZ{ std::make_unique<SwapCommand>() }
{}

bool InputHandler::isPressed(int n)
{
	return false;
}

Command* InputHandler::handleInput()
{
	if (isPressed('x')) return m_btnX.get();
	if (isPressed('y')) return m_btnY.get();
	if (isPressed('z')) return m_btnZ.get();

	return nullptr;
}