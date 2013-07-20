#pragma once
#ifndef SHOPSTATE_H
#define SHOPSTATE_H

#include "gamestate.h"
#include "Engine/Timer.h"
#include <sstream>

class FontInfo;
class NSprite;
class Shop;


class CShopState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void KeyInput(const KeyStruct& rKeys);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pDest);

	static CShopState* Instance() {
		return &mShopstate;
	}
protected:
	CShopState() { }
private:
	static CShopState mShopstate;
	Shop* mpShop;
	SDL_Surface* mpScreen;
	SDL_Surface* mpBanner;
};

#endif