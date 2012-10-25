#pragma once
#ifndef SHARED_H
#define SHARED_H
#include "SDL_image.h"
#include "Engine/Timer.h"
#include <string>

const float M_PI = 3.14159265358979323846;
const int _WSCREEN_WIDTH = 800;
const int _WSCREEN_HEIGHT = 600;

const int _GSCREEN_WIDTH = 480;
const int _GSCREEN_HEIGHT = 600;

const int _G_BANNER_WIDTH = 160;
const int _G_UI_HEIGHT = 54;
const int _G_UI_BOTTOM = 565;

const int _G_LEVEL_WIDTH = _G_BANNER_WIDTH + 640;
const int _G_BOUNDS_WIDTH = _G_BANNER_WIDTH + _GSCREEN_WIDTH;
const int _G_BOUNDS_HEIGHT = 600;
const int _G_BULLET_SAFE_ZONE = 350;

const int _WMAX_TOTEMS = 4;

const float DEG_TO_RAD_f = 0.017453292519943295769236907684886f;

struct Point
{
  int x;
  int y;
  Point(){}
  Point(int ax, int ay): x(ax), y(ax) {}
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
};

class Shared
{
public:
	static int mod(int a, int b);
    static double distance( int x1, int y1, int x2, int y2 );
	static void setFrames(SDL_Rect* clips, int clipcount, int width, int height, int y=0);
	static void setVertFrames(SDL_Rect* clips, int clipcount, int width, int height);
    static SDL_Surface *load_image( std::string filename, bool key = false );
    static void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
	static SDL_Surface* Crop_surface(SDL_Surface* src, int x, int y, int width, int height);
	static void CheckClip(Timer &timer, int &clip, int interval, int max_clip, int reset);
	static void deleteRotationFrames(SDL_Surface*** surface, int clipcount, int startAngle, int endAngle, int rotInterval=10);
	static void setRotationFrames(SDL_Rect* clips, SDL_Surface* src, int clipcount, int width, int height,
		SDL_Surface*** dest, int startAngle, int endAngle, int destWidth, int destHeight, int pivotX, int pivotY, int rotInterval=10);
};


#endif