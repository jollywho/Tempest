/* Tempest - C++ Danmakufu Game for SDL
*
*  Copyright (C) 2013 Kevin Vollmer.
*  
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*  
ÅÅ*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
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
	void KeyInput(const SDL_Event& rEvent);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* pdest);

	static CShopState* Instance() {return &mShopstate;}
protected:
	CShopState() {}
private:
	static CShopState mShopstate;
	Shop* mpShop;
	SDL_Surface* mpScreen;
	SDL_Surface* mpBanner;
};

#endif