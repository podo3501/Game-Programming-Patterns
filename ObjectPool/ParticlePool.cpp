#include "ParticlePool.h"
#include <ranges>
#include <algorithm>
#include <assert.h>

namespace views = std::views;
using namespace OP;

Particle::Particle() :
	m_state{},
	m_framesLeft{ 0 }
{}

void Particle::Init(double x, double y, double xVel, double yVel, int lifetime)
{
	m_state.live.x = x;
	m_state.live.y = y;
	m_state.live.xVel = xVel;
	m_state.live.yVel = yVel;
	m_framesLeft = lifetime;
}

bool Particle::Animate()
{
	if (!InUse()) return false;

	m_framesLeft--;
	m_state.live.x += m_state.live.xVel;
	m_state.live.y += m_state.live.yVel;

	return m_framesLeft <= 0;
}

bool Particle::InUse() const
{
	return m_framesLeft > 0;
}

Particle* Particle::GetNext() const
{
	return m_state.next;
}
void Particle::SetNext(Particle* next)
{
	m_state.next = next;
}

////////////////////////////////////////////////////////////////////

ParticlePool::ParticlePool()
{
	m_firstAvailable = &(*m_particles.begin());

	for (auto i : views::iota(0, POOL_SIZE - 1))
		m_particles[i].SetNext(&m_particles[i + 1]);
}

void ParticlePool::Create(double x, double y, double xVel, double yVel, int lifetime)
{
	assert(m_firstAvailable != nullptr);

	Particle* newParticle = m_firstAvailable;
	m_firstAvailable = newParticle->GetNext();

	newParticle->Init(x, y, xVel, yVel, lifetime);
}

void ParticlePool::Animate()
{
	std::ranges::for_each(m_particles, [this](auto& particle) { 
		if (particle.Animate() == false) return;
		
		particle.SetNext(m_firstAvailable);
		m_firstAvailable = &particle;
		});
}

int ParticlePool::GetAvailableCount()
{
	Particle* available = m_firstAvailable;
	int count{ 0 };
	while (available->GetNext() != nullptr)
	{
		count++;
		available = available->GetNext();
	}

	return count;
}