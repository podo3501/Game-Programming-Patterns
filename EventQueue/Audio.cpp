#include "Audio.h"
#include <assert.h>
#include <ranges>
#include <algorithm>

namespace views = std::views;

std::array<PlayMessage, Audio::MAX_PENDING> Audio::m_pending;
int Audio::m_head;
int Audio::m_tail;

void Audio::Init()
{ 
	m_pending = {};
	m_head = 0;
	m_tail = 0;
}

void Audio::PlaySound(SoundId id, int volume)
{
	//플레이를 바로 하지 않고 이벤트 큐에다 넣어놓고 update할때 꺼내어서 플레이한다.
	const int nextTail = (m_tail + 1) % MAX_PENDING;
	assert(nextTail != m_head);

	for (auto i = m_head; i != m_tail; i = (i + 1) % MAX_PENDING)
	{
		if (m_pending[i].id != id) continue;

		m_pending[i].volume = std::max(volume, m_pending[i].volume);
		return;
	}

	m_pending[m_tail].id = id;
	m_pending[m_tail].volume = volume;
	m_tail = nextTail;
}

ResourceId Audio::LoadSound(SoundId soundId)
{
	return 0;
}

int Audio::FindOpenChannel()
{
	return 0;
}

void Audio::StartSound(ResourceId, int channel, int volume)
{
	return;
}

PlayMessage Audio::Update()
{
	if (m_head == m_tail) return PlayMessage{};

	PlayMessage message = m_pending[m_head];
	ResourceId resource = LoadSound(message.id);
	int channel = FindOpenChannel();
	if (channel == -1) return PlayMessage{};
	StartSound(resource, channel, message.volume);
	m_head = (m_head + 1) % MAX_PENDING;

	return message;
}