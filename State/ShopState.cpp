#include "ShopState.h"
#include "Game/Interface.h"
#include "Engine/SpriteResource.h"
#include "PlayState.h"
#include "Engine/ResourceLoader.h"
#include "Shop/Shop.h"

CShopState CShopState::mShopstate;

void CShopState::Init()
{
	printf("CShopState initialize\n");
	ClearRequest();
	ResourceLoader::ReadFile("Shop");
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

void CShopState::KeyInput(const KeyStruct& rKeys)
{
	if (rKeys.tilde) { PopState(); }
	mpShop->KeyInput(rKeys);
	if (rKeys.mouse_left) printf("%i,%i\n", rKeys.mouse_x, rKeys.mouse_y);
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
