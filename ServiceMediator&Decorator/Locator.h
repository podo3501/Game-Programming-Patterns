#pragma once

#include <string>
#include <memory>

namespace locator
{
	class Audio
	{
	public:
		virtual ~Audio() {}
		virtual void PlaySound(int soundID) = 0;
		virtual void StopSound(int soundID) = 0;
		virtual void StopAlllSounds() = 0;
	};

	class NullAudio : public Audio
	{
		virtual void PlaySound(int soundID) {}
		virtual void StopSound(int soundID) {}
		virtual void StopAlllSounds() {}
	};

	class ConsoleAudio : public Audio
	{
		virtual void PlaySound(int soundID) override;
		virtual void StopSound(int soundID) override;
		virtual void StopAlllSounds() override;
	};

	class LoggedAudio : public Audio
	{
	public:
		LoggedAudio(Audio& wrapped);
		virtual void PlaySound(int soundID) override;
		virtual void StopSound(int soundID) override;
		virtual void StopAlllSounds() override;

	private:
		void Log(const std::string& message);

		Audio& m_wrapped;
	};

	class Locator
	{
	public:
		static void Initialize();
		static Audio& GetAudio();
		static void Provide(std::unique_ptr<Audio>& service);

	private:
		static std::unique_ptr<Audio> m_service;
	};

	void EnableAudioLogging();
}
