#pragma once
#ifndef SHARED_H
#define SHARED_H
#include "SDL_image.h"
#include "Engine/Timer.h"
#include <string>

const double M_PI = 3.14159265358979323846;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const int GAMESCREEN_WIDTH = 960;
const int GAMESCREEN_HEIGHT = 720;

const int GAME_BANNER_WIDTH = 0;
const int GAME_UI_TOP = 54;
const int GAME_UI_BOTTOM = GAMESCREEN_HEIGHT - 35;
const int GAME_UI_RIGHT = WINDOW_WIDTH - GAME_BANNER_WIDTH;

const int GAME_LEVEL_WIDTH = GAME_BANNER_WIDTH + WINDOW_WIDTH;
const int GAME_BOUNDS_WIDTH = WINDOW_WIDTH;
const int GAME_BOUNDS_HEIGHT = GAMESCREEN_HEIGHT;
const int GAME_BULLETSAFE_ZONE = 350;

const int GAME_UI_MODE_X = 550;
const int GAME_UI_MODE_Y = 10;
const int MAX_TOTEMS = 4;

const int SHOP_OFFSET_X = 140;
const int SHOP_OFFSET_Y = 110;

struct Point
{
  float x;
  float y;
  Point(){}
  Point(float ax, float ay): x(ax), y(ay) {}
  Point operator-(Point op2)
  {
	this->x -= op2.x;
	this->y -= op2.y;
	return *this;
  };
};



struct HitBox
{
    SDL_Rect rect;
    int wm;
    int hm;
	HitBox(int x, int y, int w, int h) : rect(), wm(w/2), hm(h/2) 
	{
		rect.x = x; rect.y = y;
		rect.w = w; rect.h = h;
	}
};

struct KeyStruct
{
	int mouse_x;
	int mouse_y;
	bool mouse_left;
	bool mouse_right;
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
	bool ctrl;
	bool tilde;
    bool space;
    KeyStruct() { 
        std::fill(&mouse_left, &space+1, false); }
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