#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Engine/Shared.h"
const float CAMERA_NORMAL = 150.f;
const float CAMERA_FAST = 300.f;

class Camera
{
public:
	static float CameraSpeed() { return camera_speed; }
    static void Update(int playerX, Uint32 deltaTicks);
	static float CameraY2() { return yVal2; }
	static float CameraY();
	static float CameraX();
    static void JumpToStart();
    static void JumpToEnd();
	static void Reset();
	static void MoveFast();
	static void StartShake(int magnitude);
	static void DrawSurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
private:
	static float camera_speed;
    static SDL_Rect camera;
	static float yVal2;
	static bool accel;
    static float xVal;
    static float yVal;
    static float yVel;
	static bool shake;
	static int shakeCount;
	static int shakeMagnitude;
	static int shakeModifier;
	static int shakeMax;
};

#endif