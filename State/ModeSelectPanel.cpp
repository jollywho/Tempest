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
FPoint HIDE_POINT = FPoint(-500, -500);
FPoint START_POINT = FPoint(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);

ModeSelectPanel::ModeSelectPanel()
{
	printf("-ModeSelectPanel Created-\n");
	mBack = false; mForward = false;

	mpTitle = Shared::LoadImage("Image/UI/select_mode_title.png");

	//default mode sprite offscreen
	mpMode = new NSprite(HIDE_POINT.x, HIDE_POINT.y, &SpriteResource::RequestResource("UI", "mode_normal"), false, true);
	mpPanel = NULL;
	mpMenu = new Menu();
	//
    mpMenu->AddItem(WINDOW_WIDTH/2, 200, "Normal");
	mpMenu->AddItem(WINDOW_WIDTH/2, 260, "Ultra");
    mpMenu->AddItem(WINDOW_WIDTH/2, 320, "Insane");
}

ModeSelectPanel::~ModeSelectPanel()
{
	printf("-ModeSelectPanel Deleted-\n");
	if (mpPanel != NULL) {
		delete mpPanel;
		mpPanel = NULL;
	}
	SDL_FreeSurface(mpTitle);
	delete mpMode;
	delete mpMenu;

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
			mMode = START_POINT;
			delete mpMode;
			mpMode = new NSprite(mMode.x, mMode.y, 
					&SpriteResource::RequestResource("UI", GameScore::GetModeEquivalent(mpMenu->GetIndex(), true)), false, true);

			GameScore::Instance()->SetMode(mpMenu->GetIndex());
			mpPanel = new PlayerSelectPanel(); mpMenu->Reset();
		}
		if (rKeys.down) mpMenu->MoveIndex(1);
		else if (rKeys.up) mpMenu->MoveIndex(-1);
	}
}

void ModeSelectPanel::Update(const int& rDeltaTime)
{
	if (mpPanel != NULL)
	{
		mForward = mpPanel->Forward();
		if (mpPanel->Back())
		{
			mMode = HIDE_POINT;
			mpMode->SetPos(mMode);	//rehide
			mpMenu->Reset();
			delete mpPanel;
			mpPanel = NULL;
		}
		else
			mpPanel->Update(rDeltaTime);

		if (mMode.y > GAME_UI_MODE_Y) mMode.y -= 300 * rDeltaTime/1000.f;
		else mMode.y = GAME_UI_MODE_Y;
			
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
	if (mpPanel == NULL && !mForward)
		Shared::DrawSurface(0, 0, mpTitle, pDest);
	else
		mpPanel->DrawTop(pDest);
	mpMode->Draw(pDest);
}