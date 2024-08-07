#pragma once

#include <cstddef>
#include <array>

using ResourceId = std::size_t;
using SoundId = std::size_t;

struct PlayMessage
{
	SoundId id{ 0 };
	int volume{ -1 };
};

class Audio
{
public:
	static void Init();
	static void PlaySound(SoundId id, int volume);
	static PlayMessage Update();

private:
	static ResourceId LoadSound(SoundId soundId);
	static int FindOpenChannel();
	static void StartSound(ResourceId, int channel, int volume);

	static const int MAX_PENDING = 16;

	static std::array<PlayMessage, MAX_PENDING> m_pending;
	static int m_head;
	static int m_tail;
};

