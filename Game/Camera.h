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
#ifndef CAMERA_H
#define CAMERA_H

#include "Engine/Shared.h"
const float CAMERA_NORMAL = 1.f;
const float CAMERA_FAST = 2.5f;

class Camera
{
public:
	float CameraSpeed() { return msSpeed; }
    void Update(int playerX, Uint32 deltaTime);
	float CameraY2() { return msY2; }
	float CameraY() { return msY; }
	float CameraX() { return msX; }
    void JumpToStart();
    void JumpToEnd();
	void Reset();
	void MoveFast();
	void StartShake(int magnitude);
	void DrawSurface(int x, int y, SDL_Surface* pSource, SDL_Surface* destination, SDL_Rect* clip = NULL );

	static Camera* Instance() 
	{
        return &mCamera; 
	}
private:
	static Camera mCamera;
	float msSpeed;
    SDL_Rect camera;
	float msY2;
	bool msAccel;
    float msX;
    float msY;
    float msYVel;
	bool msShake;
	int msShakeCount;
	int msShakeMagnitude;
	int msShakeModifier;
	int msShakeMax;
};

#endif