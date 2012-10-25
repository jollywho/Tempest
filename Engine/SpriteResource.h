#pragma once
#ifndef SPRITERESOURCE_H
#define SPRITERESOURCE_H

#include <map>
#include <string>
#include "Shared.h"

struct SpriteInfo
{
	SDL_Surface* surface;
	SDL_Rect* clips;
	int width;
	int height;
	int interval;
	int clip_count;

	~SpriteInfo()
	{
		SDL_FreeSurface(surface);
		delete[] clips;
	}
};

struct RotationInfo
{
	SDL_Surface*** rot_surface;
	SDL_Rect* clips;
	int width;
	int height;
	int interval;
	int clip_count;
	int start;
	int end;
	int rotInterval;

	~RotationInfo()
	{
		Shared::deleteRotationFrames(rot_surface, clip_count, start, end, rotInterval);
		delete[] clips;
	}
};

class SpriteResource
{
private:
	static std::map<std::pair<std::string, std::string>, SpriteInfo*> resources;
	static std::map<std::pair<std::string, std::string>, RotationInfo*> rot_resources;
public:
	static SpriteInfo& RequestResource(std::string dirname, std::string filename);
	static RotationInfo& RequestRotationResource(std::string dirname, std::string filename);

	static void AddResource(std::string dirname, std::string filename, 
		int width, int height, int interval, int clip_count, bool vert=false);

	static void AddRotationResource(std::string dirname, std::string filename,
		int width, int height, int interval, int clip_count,
		int start, int end, int destWidth, int destHeight, 
		int pivotX, int pivotY, int rotInterval=10);

	static void ClearAllResources();
	static void ClearResourceDir(std::string dirname);
};

#endif