#pragma once
#ifndef PLAYERSELECTPANEL_H
#define PLAYERSELECTPANEL_H

#include "panel.h"

class NSprite;

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
	SDL_Surface* mpTitle;
	int mIndex;
};
 

#endif
