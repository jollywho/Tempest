#include "Camera.h"
#include "Level/Level.h"
#include "State/Playstate.h"

SDL_Rect Camera::camera;
float Camera::msSpeed = 0;
float Camera::msX = 0;
float Camera::msY = 0;
float Camera::msY2 = 0;
float Camera::msYVel = 0;
bool Camera::msAccel = false;
bool Camera::msShake = false;
int Camera::msShakeCount = 0;
int Camera::msShakeMagnitude = 0;
int Camera::msShakeModifier = 0;
int Camera::msShakeMax = 0;

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
	//mY = CPlayState::Instance()->level->levelend;
	msY += 800;
}

void Camera::Update(int playerX, Uint32 deltaTicks)
{
	msY += msSpeed;
	if (msAccel && msSpeed < CAMERA_FAST) 
		msSpeed += .05f;

	msX = ((playerX - GAME_BANNER_WIDTH)/480.f) * 160.f;

	int max = CPlayState::Instance()->mpLevel->LevelEnd();
	if (msY >= max)
		msY = (float)max;

	if (msShake)
	{
		msX += ((rand() % (msShakeMagnitude * msShakeModifier)) - (msShakeMagnitude * msShakeModifier)) * (deltaTicks/1000.f);
		msShakeCount++;
		msShakeModifier = msShakeMax - msShakeCount + 1;
		if (msShakeCount > msShakeMax)
			msShake = false; 
	}

    camera.y = msY;
	msY2 = max-msY;
}

void Camera::DrawSurface( int x, int y, SDL_Surface* pSource, SDL_Surface* pDest, SDL_Rect* pClips )
{
    SDL_Rect offset;
    offset.x = x - (Sint16)msX;
    offset.y = y - (Sint16)msY2;
    SDL_BlitSurface(pSource, pClips, pDest, &offset );
}
