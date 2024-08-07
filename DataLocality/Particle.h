#pragma once
#include <array>

class Particle
{
public:
	Particle();
	bool Update();
	int GetID() { return m_id; }

private:
	int m_id;
	int m_alive;
};

class ParticleSystem
{
public:
	ParticleSystem();
	void Show(int paticleID);
	void Update();
	int GetActive() { return m_numActive; }

private:
	void ActivateParticle(int index);
	void DeactivateParticle(int index);

	static constexpr int MAX_PARTICLES = 100000;
	std::array<Particle, MAX_PARTICLES> m_particles;
	int m_numParticles;
	int m_numActive;
};
