#pragma once
#ifndef PLAYERSELECTPANEL_H
#define PLAYERSELECTPANEL_H

#include "panel.h"
#include <list>
#include <sstream>

class NSprite;
class PlayerBullet;

class PlayerSelectPanel : public Panel
{
public:
    PlayerSelectPanel();
	~PlayerSelectPanel();

	void KeyInput(const KeyStruct& rKeys);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pDest);
	void DrawTop(SDL_Surface* pDest);
private:
	std::list<PlayerBullet*> mpBulletList;
	SDL_Surface* mpTitle;
	int mIndex;

	NSprite* mpPlayer;
};
 

#endif
