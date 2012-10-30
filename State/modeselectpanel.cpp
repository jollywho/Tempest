#include "ModeSelectPanel.h"
#include "UI/NSprite.h"
#include "Game/GameScore.h"
#include "UI/Menu.h"
#include "Engine/SpriteResource.h"
#include "playerselectpanel.h"

/*
ModeModeSelectPanel --> WeaponModeSelectPanel

Mode:
Banner Title - leftright enter/exit from offscreen
Menu - of surfaces. animate when selectedindex. stop when leaving
Menu Frame - topdown enter from under intro panels

Weapon:
Banner Title - leftright enter/exit from offscreen
Demo - downup enter from under intro panels
Some type of selector using icons

*/

ModeSelectPanel::ModeSelectPanel()
{
	printf("-ModeSelectPanel Created-\n");
	mBack = false; mForward = false;

	mpTitle = Shared::LoadImage("Image/UI/select_mode_title.png");

	mpMode = new NSprite(-500, -500, &SpriteResource::RequestResource("UI", "mode_normal.png"), false, true);
	mpPanel = NULL;
	mpMenu = new Menu();
	//
    mpMenu->AddItem(WINDOW_WIDTH/2, 200, "Normal");
	mpMenu->AddItem(WINDOW_WIDTH/2, 260, "Ultra");
    mpMenu->AddItem(WINDOW_WIDTH/2, 320, "Insane");

	mMode = FPoint(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
}

ModeSelectPanel::~ModeSelectPanel()
{
	printf("-ModeSelectPanel Deleted-\n");
	SDL_FreeSurface(mpTitle);
	delete mpMode;
}

void ModeSelectPanel::KeyInput(const KeyStruct& rKeys)
{
	if (mpPanel != NULL) 
	{
		mpPanel->KeyInput(rKeys);
	}
	else
	{
		if (rKeys.esc || rKeys.x) mBack = true;
		if (rKeys.z)
		{
			delete mpMode;
			switch(mpMenu->GetIndex())
			{
				case 1:
					mpMode = new NSprite(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, &SpriteResource::RequestResource("UI", "mode_normal.png"), false, true);
					break;
				case 2:
					mpMode = new NSprite(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, &SpriteResource::RequestResource("UI", "mode_ultra.png"), false, true);
					break;								
				case 3:									 
					mpMode = new NSprite(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, &SpriteResource::RequestResource("UI", "mode_insane.png"), false, true);
					break;
			} //swtich
			mpPanel = new PlayerSelectPanel(); mpMenu->Reset();
		} //keys.z
		if (rKeys.down) mpMenu->MoveIndex(1);
		else if (rKeys.up) mpMenu->MoveIndex(-1);
	} //not panel
}

void ModeSelectPanel::Update(const int& rDeltaTime)
{
	if (mpPanel != NULL)
	{
		mForward = mpPanel->Forward();
		if (mpPanel->Back())
		{
			mMode = FPoint(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
			mpMenu->Reset();
			delete mpPanel;
			mpPanel = NULL;
		}
		else
			mpPanel->Update(rDeltaTime);
		if (mMode.x < 550)
			mMode.x += 200 * rDeltaTime/1000.f;
		if (mMode.y > 15)
			mMode.y -= 250 * rDeltaTime/1000.f;
		mpMode->SetPos(mMode);
	}
	mpMode->Update();
	mpMenu->Update(rDeltaTime, 255);
}

void ModeSelectPanel::Draw(SDL_Surface *pDest)
{
	if (mpPanel != NULL)
		mpPanel->Draw(pDest);
	else
	{
		
		mpMenu->Draw(pDest);
	}
}

void ModeSelectPanel::DrawTop(SDL_Surface *pDest)
{
	if (!mForward)
	{
		if (mpPanel != NULL)
			mpPanel->DrawTop(pDest);
		else
			Shared::DrawSurface(0, 0, mpTitle, pDest);
	}
	mpMode->Draw(pDest);
}