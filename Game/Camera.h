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