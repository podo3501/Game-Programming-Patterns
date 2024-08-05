#pragma once

#include <memory>
#include <vector>

enum Event
{
	EVENT_ENTITY_FELL,
	EVENT_ENTITY_HIT
};

enum Achievement
{
	ACHIEVEMENT_FELL_OFF_BRIDGE,
	ACHIEVEMENT_HIT
};

class Entity
{
public:
	bool IsHero() const
	{
		return true;
	}
};

class Observer
{
public:
	virtual ~Observer() {}
	virtual void OnNotify(const Entity& entity, Event event) = 0;
};

class Achievements : public Observer
{
public:
	virtual void OnNotify(const Entity& entity, Event event) override;
	bool IsFell() { return m_fell; }
	bool IsHit() { return m_hit; }

private:
	void Unlock(Achievement achievement);

	bool m_heroIsOnBridge{ true };
	bool m_fell{ false };
	bool m_hit{ false };
};

class Subject
{
public:
	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

protected:
	void Notify(const Entity& entity, Event event);

private:
	std::vector<Observer*> m_observers;
};

class Physics : public Subject
{
public:
	void UpdateEntity(Entity& entity);
};