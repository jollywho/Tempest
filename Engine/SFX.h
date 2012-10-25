#pragma once
#ifndef SFX_H
#define SFX_H

#include <map>
#include <string>
#include "SDL_mixer.h"

class SFX
{
private:
	static std::map<std::string, Mix_Music*> music_files;
	static std::map<std::string, std::pair<int, Mix_Chunk*>> sound_files;
	static int bgm_volume;
	static int fx_volume;
	static int fx_count;
public:
	static int SetBGM(int vol);
	static int SetFX(int vol);

	static void AddMusicResource(std::string filename);
	static void AddSoundResource(std::string filename);

	static Mix_Music* RequestMusic(std::string);
	
	static void PlaySoundResource(std::string filename);
	static void PlayChannelResource(std::string filename, int channel);

	static void PauseSoundResource(std::string filename);

	static void Init_SFX();
	static void ClearAllResources();
};

#endif