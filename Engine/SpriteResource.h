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
#ifndef SPRITERESOURCE_H
#define SPRITERESOURCE_H

#include <map>
#include <string>
#include "Shared.h"

struct TextureInfo
{
	SDL_Surface* pSurface;
	int width;
	int height;
};

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
public:
	static SpriteInfo& RequestResource(std::string dirname, std::string id);
	static RotationInfo& RequestRotationResource(std::string dirname, std::string id);
	static TextureInfo& RequestTextureResource(std::string dirname, std::string id);

	static void AddResource(std::string dirname, std::string id, std::string filename,
		int width, int height, int interval, int maxClips, bool vert = false);
	
	static void AddTexture(std::string dirname, std::string id, std::string filename,
		int width, int height);

	static void AddRotationResource(std::string dirname, std::string id, std::string filename,
		int width, int height, int interval, int maxClips,
		int start, int end, int destWidth, int destHeight, 
		int pivotX, int pivotY, int rotInterval = 10);

	static void ClearAllResources();
	static void ClearResourceDir(std::string dirname);
private:
	static std::map<std::pair<std::string, std::string>, SpriteInfo*> mResources;
	static std::map<std::pair<std::string, std::string>, RotationInfo*> mRotResources;
	static std::map<std::pair<std::string, std::string>, TextureInfo*> mTxResources;
};

#endif