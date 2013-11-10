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
ÅÅ*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
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
public:
	static void Init();
	static void ClearAllResources();
	static void AddMusicResource(std::string id, std::string filename);
	static void AddSoundResource(std::string id, std::string filename);
	static void PlaySoundResource(std::string id);
	static void PlayChannelResource(std::string id, int channel);
	static void PauseSoundResource(std::string id);

	static int BgmVolume(int vol);
	static int SfxVolume(int vol);
	static Mix_Music* RequestMusic(std::string id);
private:
	static std::map<std::string, Mix_Music*> msMusicFiles;
	static std::map<std::string, std::pair<int, Mix_Chunk*>> msSoundFiles;
	static int msBgmVolume;
	static int msSfxVolume;
	static int msSoundCount;
};

#endif