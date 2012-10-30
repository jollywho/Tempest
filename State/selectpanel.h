#pragma once
#ifndef SELECTPANEL_H
#define SELECTPANEL_H

#include "panel.h"
#include <list>

class PlayerBullet;
class MType;
class SType;
class Menu;

class SelectPanel : public Panel
{
public:
    SelectPanel();
	~SelectPanel();

	void KeyInput(const KeyStruct& rKeys);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pDest);
private:
	Menu* menu;
	Menu* wpnMenu;

	bool click;

	int banner_x; int banner_y;
	int banner_tail;
	Timer exit_Timer;
	Timer size_Timer;
	SDL_Surface* modeTail;
	SDL_Surface* modeFrame;
	bool charselect;
	bool shrink; bool grow;
	SDL_Rect bannerRect;
	SDL_Surface* pl;
	SDL_Rect pl_clips[3];
	int pl_clip;
	std::list<PlayerBullet*> pl_bulletlist;
	MType* wpn1; SType* wpn2;
	Timer atkTimer;
	Timer stopTimer;
	bool swap;
};
 

#endif
