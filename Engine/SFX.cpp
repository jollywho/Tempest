#include "SFX.h"

std::map<std::string, Mix_Music*> SFX::music_files;
std::map<std::string, std::pair<int, Mix_Chunk*>> SFX::sound_files;
int SFX::fx_count = 0;
int SFX::bgm_volume = 1;
int SFX::fx_volume = 10;

void SFX::Init_SFX()
{
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) < 0)
	{
		printf("Error initializing SDL_mixer: %s\n", Mix_GetError());
	}
	Mix_AllocateChannels(32);
	Mix_VolumeMusic(bgm_volume);
	Mix_Volume(-1, fx_volume);
}

int SFX::SetBGM(int vol)
{
	bgm_volume += vol;
	if (bgm_volume < 0) bgm_volume = 0;
	if (bgm_volume > MIX_MAX_VOLUME) bgm_volume = MIX_MAX_VOLUME;

	Mix_VolumeMusic(bgm_volume);
	return bgm_volume;
}

int SFX::SetFX(int vol)
{
	fx_volume += vol;
	if (fx_volume < 0) fx_volume = 0;
	if (fx_volume > MIX_MAX_VOLUME) fx_volume = MIX_MAX_VOLUME;

	Mix_Volume(-1, fx_volume);
	return fx_volume;
}

void SFX::AddMusicResource(std::string filename)
{
	filename.insert(0, "SFX/");
	if (music_files.find(filename) == music_files.end())
	{
		printf("Added: %s\n", filename.c_str());
		music_files.insert(std::make_pair(filename, Mix_LoadMUS(filename.c_str())));
	}
}

void SFX::AddSoundResource(std::string filename)
{
	filename.insert(0, "SFX/");
	if (sound_files.find(filename) == sound_files.end())
	{
		printf("Added: %s\n", filename.c_str());
		fx_count++;
		sound_files.insert(std::make_pair(filename, std::make_pair(fx_count, Mix_LoadWAV(filename.c_str()))));
	}
}

Mix_Music* SFX::RequestMusic(std::string filename)
{
	filename.insert(0, "SFX/");
	auto temp = music_files.find(filename);
	return temp->second;
}

void SFX::PlaySoundResource(std::string filename)
{
	filename.insert(0, "SFX/");
	auto temp = sound_files.find(filename);
	Mix_PlayChannel(temp->second.first, temp->second.second, 0);
}

void SFX::PlayChannelResource(std::string filename, int channel)
{
	filename.insert(0, "SFX/");
	auto temp = sound_files.find(filename);
	Mix_PlayChannel(channel, temp->second.second, 0);
}

void SFX::PauseSoundResource(std::string filename)
{
	filename.insert(0, "SFX/");
	auto temp = sound_files.find(filename);
	Mix_Pause(temp->second.first);
}

void SFX::ClearAllResources()
{
	for (auto it = music_files.begin(); it != music_files.end();) 
	{
		Mix_PauseMusic();
		Mix_FreeMusic((*it).second);
		it = music_files.erase(it);
	}
	for (auto it = sound_files.begin(); it != sound_files.end();) 
	{
		Mix_Pause(-1);
		Mix_FreeChunk((*it).second.second);
		it = sound_files.erase(it);
	}
	Mix_CloseAudio();
}