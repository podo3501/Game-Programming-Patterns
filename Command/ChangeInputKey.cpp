#include "ChangeInputKey.h"

void Jump() {};
void FireGun() {};
void SwapWeapon() {};

void JumpCommand::Execute()
{
	Jump();
}

void FireCommand::Execute()
{
	FireGun();
}

void SwapCommand::Execute()
{
	SwapWeapon();
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

void InputHandler::handleInput()
{
	if (isPressed('x')) m_btnX->Execute();
	else if (isPressed('y')) m_btnY->Execute();
	else if (isPressed('z')) m_btnZ->Execute();
}