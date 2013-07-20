#include "ShopState.h"
#include "Engine/Shared.h"
#include "Engine/FontResource.h"
#include "Engine/SpriteResource.h"
#include "Game/Gamescore.h"
#include "Game/Interface.h"
#include "playstate.h"
#include "Shop/Shop.h"

CShopState CShopState::mShopstate;

void CShopState::Init()
{
	printf("CShopState initialize\n");
	ClearRequest();
	mpScreen =  SDL_DisplayFormatAlpha(SDL_GetVideoSurface());
	mpBanner = IMG_Load("Image/UI/shop_banner.png");
	mpShop = new Shop();
}

void CShopState::Cleanup()
{
	printf("CShopState Cleanup\n");
	SDL_FreeSurface(mpScreen);
	SDL_FreeSurface(mpBanner);
}

void CShopState::Pause()
{
	printf("CShopState Pause\n");
}

void CShopState::Resume()
{
	printf("CShopState Resume\n");
}

void CShopState::KeyInput(const KeyStruct& rKeys)
{
	if (rKeys.tilde) { PopState(); }
}

void CShopState::Update(const int& rDeltaTime) 
{
	mpShop->Update(rDeltaTime);
	CPlayState::Instance()->mpInterface->Update(rDeltaTime);
}

void CShopState::Draw(SDL_Surface* pDest) 
{
	Shared::DrawSurface(0, 0, mpScreen, pDest);
	Shared::DrawSurface(SHOP_OFFSET_X, SHOP_OFFSET_Y, mpBanner, pDest);
	mpShop->Draw(pDest);

	CPlayState::Instance()->mpInterface->Draw(pDest);
}
