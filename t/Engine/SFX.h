#pragma once
#ifndef SFX_H
#define SFX_H

#include <map>
#include <string>
#include "SDL_mixer.h"

/*
Static sound interface class.
*/
class SFX
{
private:
	static std::map<std::string, Mix_Music*> msMusicFiles;
	static std::map<std::string, std::pair<int, Mix_Chunk*>> msSoundFiles;
	static int msBgmVolume;
	static int msSfxVolume;
	static int msSoundCount;
public:
	static int BgmVolume(int vol);
	static int SfxVolume(int vol);

	static void AddMusicResource(std::string id, std::string filename);
	static void AddSoundResource(std::string id, std::string filename);

	static Mix_Music* RequestMusic(std::string id);
	
	static void PlaySoundResource(std::string id);
	static void PlayChannelResource(std::string id, int channel);

	static void PauseSoundResource(std::string id);

	static void Init();
	static void ClearAllResources();
};

#endif