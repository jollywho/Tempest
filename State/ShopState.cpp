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
#include "ShopState.h"
#include "UI/Interface.h"
#include "Engine/SpriteResource.h"
#include "PlayState.h"
#include "Engine/ResourceLoader.h"
#include "Shop/Shop.h"

CShopState CShopState::mShopstate;

void CShopState::Init()
{
	printf("CShopState initialize\n");
	ClearRequest();
	mpScreen =  SDL_DisplayFormatAlpha(SDL_GetVideoSurface());
	mpBanner = IMG_Load("Image/UI/shop_banner.png");
	mpShop = new Shop(Point(SHOP_OFFSET_X, SHOP_OFFSET_Y), Point(SHOP_OFFSET_X + 1000, SHOP_OFFSET_Y));
}

void CShopState::Cleanup()
{
	printf("CShopState Cleanup\n");
	SDL_FreeSurface(mpScreen);
	SDL_FreeSurface(mpBanner);
	delete mpShop;
}

void CShopState::Pause()
{
	printf("CShopState Pause\n");
}

void CShopState::Resume()
{
	printf("CShopState Resume\n");
}

void CShopState::KeyInput(const SDL_Event& rEvent)
{
	if (rEvent.key.keysym.sym == SDLK_BACKQUOTE) { PopState();}
	mpShop->KeyInput(rEvent);
	if (rEvent.button.button == SDL_BUTTON_LEFT) printf("%i,%i\n", rEvent.motion.x, rEvent.motion.y);
}

void CShopState::Update(const int& rDeltaTime) 
{
	mpShop->Update(rDeltaTime);
	CPlayState::Instance()->mpInterface->Update(rDeltaTime);
}

void CShopState::Draw(SDL_Surface* pdest) 
{
	Shared::DrawSurface(0, 0, mpScreen, pdest);
	Shared::DrawSurface(SHOP_OFFSET_X, SHOP_OFFSET_Y, mpBanner, pdest);
	mpShop->Draw(pdest);

	CPlayState::Instance()->mpInterface->Draw(pdest);
}
