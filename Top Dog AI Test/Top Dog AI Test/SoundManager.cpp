//Blake Sullivan - SoundManager.cpp
#include "SoundManager.h"

SoundManager::SoundManager() 
{
	m_iMusicVolume = 100;
	m_iCurrentMusic = -1;
	SetPlayMusic(true);
	SetPlaySounds(true);

	for (int i = 0; i < 9; i++) 
		{m_aSounds[i] = NULL;}
	for (int i = 0; i < 6; i++) 
		{m_aMusic[i] = NULL;}
}

void SoundManager::CloseAudio() 
{
	for (int i = 0; i < 9; i++) 
		{Mix_FreeChunk(m_aSounds[i]);}

	Mix_HaltMusic();
	for (int i = 0; i < 6; i++)
		{Mix_FreeMusic(m_aMusic[i]);}

	Mix_CloseAudio();
}

int SoundManager::InitAudio() 
{
	int i = Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers);

	if (!i) 
	{
		m_aSounds[soundBullet] = Mix_LoadWAV("Audio/Sounds/Bullet.wav");
		m_aSounds[soundMissile] = Mix_LoadWAV("Audio/Sounds/Missile.wav");
		m_aSounds[soundLaser] = Mix_LoadWAV("Audio/Sounds/Laser.wav");
		m_aSounds[soundExplosion] = Mix_LoadWAV("Audio/Sounds/Explosion.wav");
		m_aSounds[soundJet] = Mix_LoadWAV("Audio/Sounds/Jet.wav");
		m_aSounds[soundRadar] = Mix_LoadWAV("Audio/Sounds/Radaer.wav");
		m_aSounds[soundStealth] = Mix_LoadWAV("Audio/Sounds/Stealth.wav");
		m_aSounds[soundPickup] = Mix_LoadWAV("Audio/Sounds/Pickup.wav");
		m_aSounds[soundDead] = Mix_LoadWAV("Audio/Sounds/Dead.wav");
		//press = Mix_LoadWAV("sounds/Btn1.wav");
		//dice = Mix_LoadWAV("sounds/Btn5.wav");
		//bookclose = Mix_LoadWAV("sounds/BookClse.wav");

		//sapete = Mix_LoadMUS("sounds/music/Che_Sapete_Che_Cosa_E_Amor.wav");
		m_aMusic[musicMap0] = Mix_LoadMUS("Audio/Music/MAP0.ogg");
		m_aMusic[musicMap1] = Mix_LoadMUS("Audio/Music/MAP1.ogg");
		m_aMusic[musicMenus] = Mix_LoadMUS("Audio/Music/Menus.ogg");
		m_aMusic[musicResult] = Mix_LoadMUS("Audio/Music/Result.ogg");
	}
	
	return i;
}

void SoundManager::PlayMusic(string title) 
{
	if (title == "sapete") 
	{
		//Mix_PlayMusic(sapete, -1);
		Mix_VolumeMusic(m_iMusicVolume);
	}
	else 
	{
		//Framework_Exception fe("Unknown music file: " + title);
		//throw fe;
	}
}

void SoundManager::PlayMusic(int musicID)
{
	if (musicID <= musicResult && GetPlayMusic() == true && musicID != m_iCurrentMusic)
	{
		if (IsMusicPlaying() == true) {StopMusic();}
		Mix_PlayMusic(m_aMusic[musicID], -1);
		Mix_VolumeMusic(m_iMusicVolume);
		m_iCurrentMusic = musicID;
	}
	//else
	//{std::cout << "Music Not Existing." << std::endl;}
}

void SoundManager::PlayMusic(string title, int volume) 
{
	PlayMusic(title);
	SetMusicVolume(volume);
}

void SoundManager::PlayMusic(int musicID, int volume)
{
	PlayMusic(musicID);
	SetMusicVolume(volume);
}

void SoundManager::SetMusicVolume(int vol) 
{
	Mix_VolumeMusic(vol);
	m_iMusicVolume = vol;
}

void SoundManager::PlaySoundEffect(string title, int channel) 
{
	/*if (title == "press") 
		{Mix_PlayChannel(channel, press, 0);}
	else if (title == "dice") 
		{Mix_PlayChannel(channel, dice, 0);}
	else if (title == "bookclose") 
		{Mix_PlayChannel(channel, bookclose, 0);}
	else
	{
		//Framework_Exception fe("Unknown soundfx file: " + title);
		//throw fe;
	}*/
}

void SoundManager::PlaySoundEffect(int soundID, int channel) 
{
	if (soundID <= soundDead && GetPlaySounds() == true)
		{Mix_PlayChannel(channel, m_aSounds[soundID], 0);}
}

void SoundManager::StopMusic() 
{
	Mix_HaltMusic();
	m_iCurrentMusic = -1;
}

bool SoundManager::IsMusicPlaying() 
{
	if (Mix_PlayingMusic()) 
		{return true;}
	else 
		{return false;}
}

void SoundManager::SetPlayMusic(bool pm)
{
	m_bPlayMusic = pm;
}
void SoundManager::SetPlaySounds(bool ps)
{
	m_bPlaySounds = ps;
}
bool SoundManager::GetPlayMusic()
{
	return m_bPlayMusic;
}
bool SoundManager::GetPlaySounds()
{
	return m_bPlaySounds;
}