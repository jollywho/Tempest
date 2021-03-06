/* Tempest - C++ Danmakufu Game for SDL
*
*  Copyright (C) 2013 Kevin Vollmer.
*  
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*  
��*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
#include "SFX.h"

std::map<std::string, Mix_Music*> SFX::msMusicFiles;
std::map<std::string, std::pair<int, Mix_Chunk*>> SFX::msSoundFiles;
int SFX::msSoundCount = 0;
int SFX::msBgmVolume = 1;
int SFX::msSfxVolume = 1;

void SFX::Init()
{
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0)
	{
		printf("***Error initializeializing SDL_mixer: %s***\n", Mix_GetError());
	}
	Mix_AllocateChannels(32);
	Mix_VolumeMusic(msBgmVolume);
	Mix_Volume(-1, msSfxVolume);
}

int SFX::BgmVolume(int vol)
{
	msBgmVolume += vol;
	if (msBgmVolume < 0) msBgmVolume = 0;
	if (msBgmVolume > MIX_MAX_VOLUME) msBgmVolume = MIX_MAX_VOLUME;

	Mix_VolumeMusic(msBgmVolume);
	return msBgmVolume;
}

int SFX::SfxVolume(int vol)
{
	msSfxVolume += vol;
	if (msSfxVolume < 0) msSfxVolume = 0;
	if (msSfxVolume > MIX_MAX_VOLUME) msSfxVolume = MIX_MAX_VOLUME;

	Mix_Volume(-1, msSfxVolume);
	return msSfxVolume;
}

void SFX::AddMusicResource(std::string id, std::string filename)
{
	filename.insert(0, "SFX/");
	if (msMusicFiles.find(id) == msMusicFiles.end())
	{
		printf("Added: %s\n", filename.c_str());
		msMusicFiles.insert(std::make_pair(id, Mix_LoadMUS(filename.c_str())));
	}
}

void SFX::AddSoundResource(std::string id, std::string filename)
{
	filename.insert(0, "SFX/");
	if (msSoundFiles.find(id) == msSoundFiles.end())
	{
		Mix_Chunk* sound = Mix_LoadWAV(filename.c_str());
		if (sound == NULL)
			printf("***Error Opening: %s***\n", filename.c_str());
		else
		{
			printf("Added: %s\n", filename.c_str());
			msSoundCount++;
			msSoundFiles.insert(std::make_pair(id, std::make_pair(msSoundCount, sound)));
		}
	}
}

Mix_Music* SFX::RequestMusic(std::string id)
{
	auto temp = msMusicFiles.find(id);
	return temp->second;
}

void SFX::PlaySoundResource(std::string id)
{
	auto temp = msSoundFiles.find(id);
	Mix_PlayChannel(temp->second.first, temp->second.second, 0);
}

void SFX::PlayChannelResource(std::string id, int channel)
{
	auto temp = msSoundFiles.find(id);
	Mix_PlayChannel(channel, temp->second.second, 0);
}

void SFX::PauseSoundResource(std::string id)
{
	auto temp = msSoundFiles.find(id);
	Mix_Pause(temp->second.first);
}

void SFX::ClearAllResources()
{
	for (auto it = msMusicFiles.begin(); it != msMusicFiles.end();) 
	{
		Mix_PauseMusic();
		Mix_FreeMusic((*it).second);
		it = msMusicFiles.erase(it);
	}
	for (auto it = msSoundFiles.begin(); it != msSoundFiles.end();) 
	{
		Mix_Pause(-1);
		Mix_FreeChunk((*it).second.second);
		it = msSoundFiles.erase(it);
	}
	Mix_CloseAudio();
}