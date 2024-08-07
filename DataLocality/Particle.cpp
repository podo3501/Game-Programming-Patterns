#include "Particle.h"
#include <ranges>
#include <algorithm>
#include <assert.h>

namespace views = std::views;

Particle::Particle()
{
	static int id = 0;
	m_alive = id;
	m_id = id++;
}

bool Particle::Update()
{
	m_alive--;
	if (m_alive < 0) return false;

	return true;
}

ParticleSystem::ParticleSystem() :
	m_particles{},
	m_numParticles{},
	m_numActive{ 0 }
{}

void ParticleSystem::Show(int particleID)
{
	auto find = std::ranges::find_if(m_particles, [particleID](auto& particle) { return particle.GetID() == particleID; });
	auto index = static_cast<int>(std::distance(m_particles.begin(), find));

	ActivateParticle(index);
}

void ParticleSystem::Update()
{
	for (int i = 0; i < m_numActive; )
	{
		bool alive = m_particles[i].Update();
		if (alive)
			i++;	//�ڸ��� �¹ٲٸ� ����Ű�� ���Ұ� �޶����� �Ǿ� �������Ѵ�.
		else
			DeactivateParticle(i);
	}
}

void ParticleSystem::ActivateParticle(int index)
{
	assert(index >= m_numActive);
	
	//���� Ȱ���� ���� ��Ȱ�� 7���̶� �ٲ۴ٸ� 0, 7�� ���� ����� �ٲ۴�.
	std::swap(m_particles[m_numActive], m_particles[index]);
	m_numActive++;
}

void ParticleSystem::DeactivateParticle(int index)
{
	assert(index < m_numActive);

	m_numActive--;
	std::swap(m_particles[m_numActive], m_particles[index]);
}