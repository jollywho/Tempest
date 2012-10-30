#include "PlayerSelectPanel.h"
#include "UI/NSprite.h"
#include "Game/GameScore.h"
#include "UI/Menu.h"
#include "Engine/SpriteResource.h"

/*
ModePlayerSelectPanel --> WeaponPlayerSelectPanel

Mode:
Banner Title - leftright enter/exit from offscreen
Menu - of surfaces. animate when selectedindex. stop when leaving
Menu Frame - topdown enter from under intro panels

Weapon:
Banner Title - leftright enter/exit from offscreen
Demo - downup enter from under intro panels
Some type of selector using icons

*/

PlayerSelectPanel::PlayerSelectPanel()
{
	printf("-PlayerSelectPanel Created-\n");
	mBack = false; mForward = false;

	mpTitle = Shared::LoadImage("Image/UI/select_player_title.png");
	mIndex = 1;
}

PlayerSelectPanel::~PlayerSelectPanel()
{
	printf("-PlayerSelectPanel Deleted-\n");
	SDL_FreeSurface(mpTitle);
}

void PlayerSelectPanel::KeyInput(const KeyStruct& rKeys)
{
	if (rKeys.esc || rKeys.x) mBack = true;
	if (rKeys.z)
	{
		mForward = true;
	} //keys.z
	if (rKeys.down) mIndex++;
	else if (rKeys.up) mIndex--;
	if (mIndex > 3) mIndex = 1;
	if (mIndex < 1) mIndex = 3;
}

void PlayerSelectPanel::Update(const int& rDeltaTime)
{

}

void PlayerSelectPanel::Draw(SDL_Surface *pDest)
{

}

void PlayerSelectPanel::DrawTop(SDL_Surface *pDest)
{
	Shared::DrawSurface(0,0, mpTitle, pDest);
}