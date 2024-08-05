#pragma once

#include <memory>

enum Input
{
	RELEASE_DOWN,
	PRESS_DOWN,
};

class Heroine;

class HeroineState
{
public:
	virtual ~HeroineState() {};
	virtual std::unique_ptr<HeroineState> HandleInput(Heroine& heroine, Input input) = 0;
	virtual void Enter(Heroine& heroine) = 0;
	virtual void Leave(Heroine& heroine) = 0;
	virtual void Update(Heroine& heroine) = 0;
};

/////////////////////////////////////////////////////////////////////

class DuckingState : public HeroineState
{
public:
	DuckingState();

	virtual std::unique_ptr<HeroineState> HandleInput(Heroine& heroine, Input input) override;
	virtual void Enter(Heroine& heroine) override;
	virtual void Leave(Heroine& heroine) override;
	virtual void Update(Heroine& heroine) override;

private:
	int m_chargeTime;
};

/////////////////////////////////////////////////////////////////////

class StandingState : public HeroineState
{
public:
	StandingState();

	virtual std::unique_ptr<HeroineState> HandleInput(Heroine& heroine, Input input) override;
	virtual void Enter(Heroine& heroine) override;
	virtual void Leave(Heroine& heroine) override;
	virtual void Update(Heroine& heroine) override;
};

/////////////////////////////////////////////////////////////////////

enum Image
{
	IMAGE_NONE,
	IMAGE_STAND,
	IMAGE_DUCKING,
};

class Heroine
{
public:
	Heroine();

	void HandleInput(Input input);
	void Update();

	void SetGraph(Image image);
	Image GetGraph();
	void SuperBomb();

private:
	std::unique_ptr<HeroineState> m_state;
	Image m_image;
};


