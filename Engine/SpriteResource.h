#pragma once
#ifndef SPRITERESOURCE_H
#define SPRITERESOURCE_H

#include <map>
#include <string>
#include "Shared.h"

struct SpriteInfo
{
	SDL_Surface* pSurface;
	SDL_Rect* pClips;
	int width;
	int height;
	int interval;
	int maxClips;

	~SpriteInfo()
	{
		SDL_FreeSurface(pSurface);
		delete[] pClips;
	}
};

struct RotationInfo
{
	SDL_Surface*** pSurface;
	SDL_Rect* pClips;
	int width;
	int height;
	int interval;
	int maxClips;
	int start;
	int end;
	int rotInterval;

	~RotationInfo()
	{
		Shared::DeleteRotationFrames(pSurface, maxClips, start, end, rotInterval);
		delete[] pClips;
	}
};

class SpriteResource
{
private:
	static std::map<std::pair<std::string, std::string>, SpriteInfo*> mResources;
	static std::map<std::pair<std::string, std::string>, RotationInfo*> mRotResources;
public:
	static SpriteInfo& RequestResource(std::string dirname, std::string filename);
	static RotationInfo& RequestRotationResource(std::string dirname, std::string filename);

	static void AddResource(std::string dirname, std::string filename, 
		int width, int height, int interval, int maxClips, bool vert=false);

	static void AddRotationResource(std::string dirname, std::string filename,
		int width, int height, int interval, int maxClips,
		int start, int end, int destWidth, int destHeight, 
		int pivotX, int pivotY, int rotInterval=10);

	static void ClearAllResources();
	static void ClearResourceDir(std::string dirname);
};

#endif