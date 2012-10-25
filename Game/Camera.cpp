#include "Camera.h"
#include "Level/Level.h"
#include "State/Playstate.h"

SDL_Rect Camera::camera;
Timer Camera::span_Timer;
float Camera::camera_speed = 0;
float Camera::xVal = 0;
float Camera::yVal = 0;
float Camera::yVel = 0;
float Camera::yVal2 = 0;
float Camera::CameraY() { return yVal; }
float Camera::CameraX() { return xVal; }
bool Camera::accel = false;
bool Camera::shake = false;
int Camera::shakeCount = 0;
int Camera::shakeMagnitude = 0;
int Camera::shakeModifier = 0;
int Camera::shakeMax = 0;

void Camera::JumpToStart()
{
    xVal = -50;
    yVal = _GSCREEN_HEIGHT;
    camera.w = _GSCREEN_WIDTH;
    camera.h = _GSCREEN_HEIGHT;
	yVal2 = 0;
}

void Camera::Reset()
{
	camera_speed = CAMERA_NORMAL;
	accel = false;
	span_Timer.start();
}

void Camera::MoveFast()
{
	accel = true;
}

void Camera::StartShake(int magnitude)
{
	shake = true;
	shakeCount = 0;
	shakeMagnitude = magnitude;
	shakeModifier = 200;
	shakeMax = (rand() % 50)+(shakeMagnitude * 20);
}

void Camera::JumpToEnd()
{
	//yVal = CPlayState::Instance()->level->levelend;
	yVal += 800;
}

void Camera::Update(int playerX, Uint32 deltaTicks)
{
	yVal += camera_speed;
	span_Timer.start();
	if (accel && camera_speed < CAMERA_FAST) 
		camera_speed += .05f;

	xVal = ((playerX - _G_BANNER_WIDTH)/480.f) * 160.f;

	int max = CPlayState::Instance()->level->GetLevelEnd();
	if (yVal >= max)
		yVal = (float)max;

	if (shake)
	{
		xVal += ((rand() % (shakeMagnitude * shakeModifier)) - (shakeMagnitude * shakeModifier)) * (deltaTicks/1000.f);
		shakeCount++;
		shakeModifier = shakeMax - shakeCount + 1;
		if (shakeCount > shakeMax)
			shake = false; 
	}

    camera.y = yVal;
	yVal2 = max-yVal;
}

void Camera::DrawSurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )
{
    SDL_Rect offset;
    offset.x = x - (Sint16)xVal;
    offset.y = y - (Sint16)yVal2;
    SDL_BlitSurface( source, clip, destination, &offset );
}
