#include "Achievement.h"
#include <ranges>

void Achievements::OnNotify(const Entity& entity, Event event)
{
	switch (event)
	{
	case EVENT_ENTITY_FELL:
		if (entity.IsHero() && m_heroIsOnBridge)
		{
			Unlock(ACHIEVEMENT_FELL_OFF_BRIDGE);
			m_heroIsOnBridge = false;
		}
	case EVENT_ENTITY_HIT:
		if (entity.IsHero())
		{
			Unlock(ACHIEVEMENT_HIT);
		}
		break;
	}
}

void Achievements::Unlock(Achievement achievement)
{
	switch (achievement)
	{
	case ACHIEVEMENT_FELL_OFF_BRIDGE:
		m_fell = true;
		break;
	case ACHIEVEMENT_HIT:
		m_hit = true;
		break;
	}
}

void Subject::AddObserver(Observer* observer)
{
	m_observers.emplace_back(observer);
}

void Subject::RemoveObserver(Observer* observer)
{
	std::erase(m_observers, observer);
}

void Subject::Notify(const Entity& entity, Event event)
{
	for (auto i : std::views::iota(0, static_cast<int>(m_observers.size())))
	{
		m_observers[i]->OnNotify(entity, event);
	}
}

void Physics::UpdateEntity(Entity& entity)
{
	Notify(entity, EVENT_ENTITY_FELL);
	Notify(entity, EVENT_ENTITY_HIT);
}