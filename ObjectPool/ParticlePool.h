#pragma once
#include <array>

namespace OP
{
	class Particle
	{
	public:
		Particle();
		void Init(double x, double y, double xVel, double yVel, int lifetime);
		bool Animate();
		bool InUse() const;

		Particle* GetNext() const;
		void SetNext(Particle* next);

	private:
		int m_framesLeft;

		union
		{
			struct //사용중일때의 상태
			{
				double x, y;
				double xVel, yVel;
			} live;

			//사용중이 아닐때의 상태
			Particle* next{ nullptr };
		} m_state;
	};

	class ParticlePool
	{
	public:
		ParticlePool();

		void Create(double x, double y, double xVel, double yVel, int lifetime);
		void Animate();
		int GetAvailableCount();

	private:
		static constexpr int POOL_SIZE = 100;
		std::array<Particle, POOL_SIZE> m_particles;

		Particle* m_firstAvailable;
	};
}