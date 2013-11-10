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
#include "Shared.h"
#include "sprig.h"
#include <cmath>
#include <iostream>

SDL_Surface* Shared::LoadImage(std::string filename, bool key)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load(filename.c_str());

    if(loadedImage != NULL)
    {
        if (key)
            optimizedImage = SDL_DisplayFormat(loadedImage);
        else
            optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
        SDL_FreeSurface(loadedImage);
    }
	else
		printf("***Error loading file : %s ***\n", filename);

    return optimizedImage;
}

void Shared::DrawSurface(int x, int y, SDL_Surface* pSource, SDL_Surface* destination, SDL_Rect* pClips)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(pSource, pClips, destination, &offset);
}

void Shared::CheckClip(Timer &rTimer, int &rClip, int interval, int maxClip, int reset)
{
	if (rTimer.GetTicks() > interval)
    { 
        if (rClip < maxClip - 1)
            rClip++;
        else
            rClip = reset;
        rTimer.Start();
	}
}

void Shared::SetFrames(SDL_Rect* clips, int maxClips, int width, int height, int y)
{
	for (int i = 0; i <= maxClips - 1; i++)
	{
        clips[i].x = i * width;
        clips[i].y = y;
        clips[i].w = width; 
        clips[i].h = height;
	}
}

void Shared::SetVertFrames(SDL_Rect* clips, int maxClips, int width, int height)
{
	for (int i = 0; i <= maxClips - 1; i++)
	{
        clips[i].x = 0;
        clips[i].y = i * height;
        clips[i].w = width; 
        clips[i].h = height;
	}
}

SDL_Surface* Shared::CropSurface(SDL_Surface* src, int x, int y, int width, int height)
{
    SDL_Surface* temp = SPG_CreateSurface(0, width, height);
    SDL_Rect rect = {x, y, width, height};
	SPG_PushBlend(SPG_SRC_ALPHA);
    SPG_Blit(src, &rect, temp, NULL);
	SDL_Surface* dest = SDL_DisplayFormat(temp);
	SPG_PopBlend();
	SDL_FreeSurface(temp);
	return dest;
}

void Shared::SetRotationFrames(SDL_Rect* clips, SDL_Surface* pSrc, int maxClips,
	int width, int height, SDL_Surface*** pdest, int startAngle, int endAngle,
	int destWidth, int destHeight, int pivotX, int pivotY, int rotInterval)
{
	int angle = endAngle - startAngle;
	for (int i = 0; i < maxClips; i++)
	{
		pdest[i] = new SDL_Surface*[angle];
		for (int k = startAngle; k < endAngle; k += rotInterval)
		{
			SDL_Surface* tempSrc = SPG_CreateSurface(0, width, height);
			SDL_Surface* tempdest = SPG_CreateSurface(0, width * 2, height * 2);
			SPG_PushBlend(SPG_SRC_ALPHA);
			SPG_Blit(pSrc, &clips[i], tempSrc, NULL);
			SPG_TransformX(tempSrc, tempdest, -k, 1, 1, pivotX, pivotY, destWidth, destHeight,
				SPG_TAA | SPG_TSAFE);
			SPG_PopBlend();
			pdest[i][k] = SDL_DisplayFormatAlpha(tempdest);
			SDL_FreeSurface(tempSrc);
			SDL_FreeSurface(tempdest);
		}
	}
}

void Shared::DeleteRotationFrames(SDL_Surface*** surface, int maxClips, int startAngle,
	int endAngle, int rotInterval)
{
	int mAngle = endAngle - startAngle;
	for (int i = 0; i < maxClips; i++)
	{
		for (int k = startAngle; k < endAngle; k += rotInterval)
		{
			SDL_FreeSurface(surface[i][k]);
		}
	}
}

int Shared::Mod(int a, int b)
{
   int ret = a % b;
   if(ret < 0) { ret+=b;}
   return ret;
}

double Shared::Distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow((double)x2 - x1, (int)2) + pow((double)y2 - y1, (int)2));
}
