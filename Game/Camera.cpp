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
#include "Camera.h"
#include "Level/Level.h"
#include "State/Playstate.h"

Camera Camera::mCamera;

void Camera::JumpToStart()
{
    msX = -50;
    msY = GAMESCREEN_HEIGHT;
    camera.w = GAMESCREEN_WIDTH;
    camera.h = GAMESCREEN_HEIGHT;
	msY2 = 0;
}

void Camera::Reset()
{
	msX = -50;
	msY = GAMESCREEN_HEIGHT;
	msSpeed = CAMERA_NORMAL;
	msAccel = false;
}

void Camera::MoveFast()
{
	msAccel = true;
}

void Camera::StartShake(int magnitude)
{
	msShake = true;
	msShakeCount = 0;
	msShakeMagnitude = magnitude;
	msShakeModifier = 200;
	msShakeMax = (rand() % 50)+(msShakeMagnitude * 20);
}

void Camera::JumpToEnd()
{
	msY += 800;
}

void Camera::Update(int playerX, Uint32 delta_ticks)
{
	msY += msSpeed;
	if (msAccel && msSpeed < CAMERA_FAST) 
		msSpeed += .05f;

	msX = ((playerX - GAME_BANNER_WIDTH) / 480.f) * 160.f;
	
	int max = CPlayState::Instance()->mpLevel->LevelEnd();
	if (msY >= max)
		msY = (float)max;

	if (msShake)
	{
		msX += ((rand() % (msShakeMagnitude * msShakeModifier)) -
			(msShakeMagnitude * msShakeModifier)) *
			(delta_ticks / 1000.f);
		msShakeCount++;
		msShakeModifier = msShakeMax - msShakeCount + 1;
		if (msShakeCount > msShakeMax)
			msShake = false; 
	}

    camera.y = msY;
	msY2 = max-msY;
}

void Camera::DrawSurface(int x, int y, SDL_Surface* pSource, SDL_Surface* pdest, SDL_Rect* pClips)
{
    SDL_Rect offset;
    offset.x = x - (Sint16)msX;
    offset.y = y - (Sint16)msY2;
    SDL_BlitSurface(pSource, pClips, pdest, &offset);
}
