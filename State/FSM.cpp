#include "FSM.h"

DuckingState::DuckingState() :
	m_chargeTime{ 0 }
{}

std::unique_ptr<HeroineState> DuckingState::HandleInput(Heroine& heroine, Input input)
{
	if (input == RELEASE_DOWN)
		return std::make_unique<StandingState>();

	return nullptr;
}

void DuckingState::Enter(Heroine& heroine)
{
	heroine.SetGraph(IMAGE_DUCKING);
}

void DuckingState::Leave(Heroine& heroine)
{
	return;
}

void DuckingState::Update(Heroine& heroine)
{
	constexpr int MAX_CHARGE = 100;

	m_chargeTime++;
	if (m_chargeTime > MAX_CHARGE)
	{
		heroine.SuperBomb();
	}
}

/////////////////////////////////////////////////////////////////////

StandingState::StandingState()
{}

std::unique_ptr<HeroineState> StandingState::HandleInput(Heroine& heroine, Input input)
{
	if (input == PRESS_DOWN)
		return std::make_unique<DuckingState>();

	return nullptr;
}

void StandingState::Enter(Heroine& heroine)
{
	heroine.SetGraph(IMAGE_STAND);
}

void StandingState::Leave(Heroine& heroine)
{
	return;
}

void StandingState::Update(Heroine& heroine)
{}

/////////////////////////////////////////////////////////////////////

Heroine::Heroine() :
	m_state{ std::make_unique<StandingState>() },
	m_image{ IMAGE_STAND }
{}

void Heroine::HandleInput(Input input)
{
	std::unique_ptr<HeroineState> state = m_state->HandleInput(*this, input);
	if (state == nullptr)
		return;

	m_state->Leave(*this);
	m_state = std::move(state);
	m_state->Enter(*this);
}

void Heroine::Update()
{
	m_state->Update(*this);
}

void Heroine::SuperBomb()
{}

void Heroine::SetGraph(Image image)
{
	m_image = image;
}

Image Heroine::GetGraph()
{
	return m_image;
}