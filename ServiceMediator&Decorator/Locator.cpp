#include "Locator.h"

using namespace locator;

void ConsoleAudio::PlaySound(int soundID)
{}

void ConsoleAudio::StopSound(int soundID)
{}

void ConsoleAudio::StopAlllSounds()
{}

///////////////////////////////////////////////////////////////////////////////

LoggedAudio::LoggedAudio(Audio& wrapped) :
	m_wrapped(wrapped)
{}

void LoggedAudio::PlaySound(int soundID)
{
	Log("사운드 출력");
	m_wrapped.PlaySound(soundID);
}

void LoggedAudio::StopSound(int soundID)
{
	Log("사운드 중지");
	m_wrapped.StopSound(soundID);
}

void LoggedAudio::StopAlllSounds()
{
	Log("모든 사운드 중지");
	m_wrapped.StopAlllSounds();
}

void LoggedAudio::Log(const std::string& message)
{
	return;
}

///////////////////////////////////////////////////////////////////////////////

std::unique_ptr<locator::Audio> Locator::m_service{ nullptr };

std::unique_ptr<NullAudio> CreateNullAudio()
{
	return std::move(std::make_unique<NullAudio>());
}

void Locator::Initialize()
{
	m_service = CreateNullAudio();
}

Audio& Locator::GetAudio()
{
	return *m_service.get();
}

void Locator::Provide(std::unique_ptr<Audio>& service)
{
	if (service == nullptr)
		m_service = CreateNullAudio();

	m_service = std::move(service);
}

///////////////////////////////////////////////////////////////////////////////

void EnableAudioLogging()
{
	std::unique_ptr<Audio> loggedAudio = std::make_unique<LoggedAudio>(Locator::GetAudio());
	Locator::Provide(loggedAudio);
}