#pragma once
#ifndef SHARED_H
#define SHARED_H
#include "SDL_image.h"
#include "Engine/Timer.h"
#include <string>

const double M_PI = 3.14159265358979323846;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int GAMESCREEN_WIDTH = 480;
const int GAMESCREEN_HEIGHT = 600;

const int GAME_BANNER_WIDTH = 160;
const int GAME_UI_TOP = 54;
const int GAME_UI_BOTTOM = 565;

const int GAME_LEVEL_WIDTH = GAME_BANNER_WIDTH + 640;
const int GAME_BOUNDS_WIDTH = GAME_BANNER_WIDTH + GAMESCREEN_WIDTH;
const int GAME_BOUNDS_HEIGHT = 600;
const int GAME_BULLETSAFE_ZONE = 350;

const int MAX_TOTEMS = 4;

const float DEG_TO_RAD_f = 0.017453292519943295769236907684886f;

struct Point
{
  int x;
  int y;
  Point(){}
  Point(int ax, int ay): x(ax), y(ay) {}
};

struct FPoint
{
  float x;
  float y;
  FPoint(){}
  FPoint(float ax, float ay): x(ax), y(ay) {}
};

struct KeyStruct
{
	bool left;
	bool right;
	bool up;
	bool down;
	bool z;
	bool x;
	bool enter;
	bool shift;
	bool esc;
	bool none;
	KeyStruct() { 
		std::fill(&left, &none+1, false); }
};

class Shared
{
public:
	static SDL_Surface* LoadImage( std::string filename, bool colorKey = false );

	static void DrawSurface( int x, int y, SDL_Surface* pSource, SDL_Surface* pDest, SDL_Rect* pClips = NULL );

	static void CheckClip(Timer &rTimer, int &rClip, int interval, int maxClip, int reset);

	static void SetFrames(SDL_Rect* pClips, int maxClips, int width, int height, int y=0);

	static void SetVertFrames(SDL_Rect* pClips, int maxClips, int width, int height);
    
	static SDL_Surface* CropSurface(SDL_Surface* pSrc, int x, int y, int width, int height);

	static void SetRotationFrames(SDL_Rect* pClips, SDL_Surface* pSrc, int maxClips, int width, int height,

		SDL_Surface*** pDest, int startAngle, int endAngle, int destWidth, int destHeight, int pivotX, int pivotY, int rotInterval=10);

	static void DeleteRotationFrames(SDL_Surface*** pSrc, int maxClips, int startAngle, int endAngle, int rotInterval=10);

	static int Mod(int a, int b);

	static double Distance( int x1, int y1, int x2, int y2 );
};


#endif