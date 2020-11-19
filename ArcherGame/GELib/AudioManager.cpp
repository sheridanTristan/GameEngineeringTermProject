
#include <algorithm>
#include "AudioManager.h"


AudioManager::AudioManager()
{

}

bool AudioManager::Init()
{

	if (Mix_Init(MIX_INIT_MP3) == 0)
	{
		cout << "Mixer init failed\n";
		return false;
	}
	else
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);
		Mix_AllocateChannels(16);
		return true;
	}
}

void AudioManager::SetMusicVolume(int volLevel)
{
	int clampedVolume =
		std::clamp(volLevel, 0, 128);

	Mix_VolumeMusic(clampedVolume);

}



void AudioManager::PlayMusic(const char * id, int loops)
{
	AudioTrack<Mix_Music*> session = m_MusicTracks[id];
	Mix_PlayMusic(session.GetAudioObject(), loops);

}

void AudioManager::PlaySound(const char* id, int channel, int loops)
{
	AudioTrack<Mix_Chunk*> session = m_Sounds[id];
	Mix_PlayChannel(channel,session.GetAudioObject(), loops);
}


void AudioManager::LoadMusic(const char* path,AudioScope scope, string key)
{
	//check if it is loadable first...
	Mix_Music* t = Mix_LoadMUS(path);
	if (t != nullptr)
	{
		m_MusicTracks[key] = AudioTrack<Mix_Music*>(scope, t);
		
		
	}
	else
	{
		//error
		cout << "Music load failed. \n" << Mix_GetError();
	}
}

void AudioManager::LoadSound(const char* path, AudioScope scope, string key)
{
	Mix_Chunk* t = Mix_LoadWAV(path);
	if (t != nullptr)
		m_Sounds[key] = AudioTrack<Mix_Chunk*>(scope, t);
	else
		cout << "Sound load failed. \n";
}

void AudioManager::ToggleMusic()
{
	//Mix_PausedMusic() returns 1 if paused.
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();

}

void AudioManager::UnloadMusic(AudioScope scope)
{
	std::map<string, AudioTrack<Mix_Music*>> tracks = m_MusicTracks;
	for (auto& track : tracks) {
		if ((track.second.GetScope() & scope) == track.second.GetScope()) {
			Mix_FreeMusic(track.second.GetAudioObject());
			m_MusicTracks.erase(track.first);
		}

	}

}

void AudioManager::UnloadSound(AudioScope scope)
{
	std::map<string, AudioTrack<Mix_Chunk*>> tracks = m_Sounds;
	for (auto& track : m_Sounds) {
		if ((track.second.GetScope() & scope)  == track.second.GetScope()) {
			Mix_FreeChunk(track.second.GetAudioObject());
			m_Sounds.erase(track.first);
		}

	}
}

AudioManager::~AudioManager()
{
	UnloadMusic((AudioScope)(AudioScope::GLOBAL | AudioScope::SESSION));
	UnloadSound((AudioScope)(AudioScope::GLOBAL | AudioScope::SESSION));

	Mix_CloseAudio();
	Mix_Quit();
}

template<class T>
AudioTrack<T>::AudioTrack(AudioScope scope, T obj) : m_obj(obj),m_Scope(scope)
{

}