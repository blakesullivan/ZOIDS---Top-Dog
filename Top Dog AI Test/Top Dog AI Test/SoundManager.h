//Blake Sullivan - SoundManger.h
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL_mixer.h>
#include "StateHeader.h"
#include <fstream>
#include <vector>
#include <string>
using std::string;

class SoundManager 
{
private:
	static const int audio_rate = 44100;
	static const Uint16 audio_format = AUDIO_S16;
	static const int audio_channels = 2;
	static const int audio_buffers = 4096;

	Mix_Chunk* m_aSounds[9];
	Mix_Music* m_aMusic[6];

	int m_iMusicVolume, m_iCurrentMusic;
	bool m_bPlayMusic, m_bPlaySounds;

public:
	SoundManager();

	void CloseAudio();
	int InitAudio();
	void PlayMusic(string title);
	void PlayMusic(string title, int volume);
	void PlayMusic(int musicID, int volume);
	void PlayMusic(int musicID);
	void SetMusicVolume(int vol);
	void PlaySoundEffect(string title, int channel);
	void PlaySoundEffect(int soundID, int channel);
	void StopMusic();

	bool IsMusicPlaying();

	void SetPlayMusic(bool);
	void SetPlaySounds(bool);
	bool GetPlayMusic();
	bool GetPlaySounds();
};
#endif