#pragma once
#include <vector>
#include "SDL_mixer.h"  //required for audio
#include <iostream>
#include <map>
using namespace std;
enum AudioScope {
	SESSION,
	GLOBAL
};
template <typename T>
 class AudioTrack {
	
private:
	AudioScope m_Scope;
	T m_obj;
	
public:
	AudioTrack(){}
	AudioTrack(AudioScope scope, T obj);
	AudioScope GetScope() { return m_Scope; }
	T GetAudioObject() { return m_obj; }
	
};

class AudioManager
{
private:

	
	int soundToggle;
	int musicToggle;


	map<string, AudioTrack<Mix_Music*>> m_MusicTracks;
	map<string, AudioTrack<Mix_Chunk*>> m_Sounds;


public:
	AudioManager();
	~AudioManager();
	bool Init();

	//Set volume of the music
	void SetMusicVolume(int volLevel);

	///loops=-1 means infinite
	void PlayMusic(const char * id, int loops = -1);


	void PlaySound(const char* id, int channel = -1, int loops = 0);


	void LoadMusic(const char* path,AudioScope scope, string key);
	void LoadSound(const char* path, AudioScope, string key);


	void UnloadMusic(AudioScope scope);
	void UnloadSound(AudioScope scope);

	//Toggle music:: so that you can pause and resume the current music track
	void ToggleMusic();
	void ToggleSound();


};


