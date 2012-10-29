#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Engine/Shared.h"
const float CAMERA_NORMAL = 1.f;
const float CAMERA_FAST = 2.5f;

class Camera
{
public:
	static float CameraSpeed() { return msSpeed; }
    static void Update(int playerX, Uint32 deltaTime);
	static float CameraY2() { return msY2; }
	static float Camera::CameraY() { return msY; }
	static float Camera::CameraX() { return msX; }
    static void JumpToStart();
    static void JumpToEnd();
	static void Reset();
	static void MoveFast();
	static void StartShake(int magnitude);
	static void DrawSurface(int x, int y, SDL_Surface* pSource, SDL_Surface* destination, SDL_Rect* clip = NULL );
private:
	static float msSpeed;
    static SDL_Rect camera;
	static float msY2;
	static bool msAccel;
    static float msX;
    static float msY;
    static float msYVel;
	static bool msShake;
	static int msShakeCount;
	static int msShakeMagnitude;
	static int msShakeModifier;
	static int msShakeMax;
};

#endif