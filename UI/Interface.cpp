#include "Interface.h"
#include "Engine/SpriteResource.h"
#include "Engine/FontResource.h"
#include "Game/Savescore.h"
#include "NSprite.h"
#include "Shop/Inventory.h"
#include "Title.h"

Interface::Interface() 
{
	printf("Interface Created\n");
	GameScore::Instance()->ResetGame();
	mpRedFont = &FontResource::RequestFont("gold_block");
	mpInv = new Inventory();
	mpTitle = new Title("FOREST OF WIND");

	/* Scores */ //todo: get a fixed width font for scores
	int max_score_width = mpRedFont->pFont->getWidth("123456789012345")/2;
	mpMode = new NSprite(WINDOW_WIDTH/2, GAME_UI_MODE_Y, 
		&SpriteResource::RequestResource("UI", GameScore::Instance()->GetModeString()), false, true);
	mpPlayer = new NSprite(WINDOW_WIDTH * 0.25 - max_score_width/2, GAME_UI_MODE_Y, 
		&SpriteResource::RequestResource("UI", "player_title"), false, true);
	mpHigh = new NSprite(WINDOW_WIDTH * 0.75 + max_score_width/2, GAME_UI_MODE_Y, 
		&SpriteResource::RequestResource("UI", "high_title"), false);

	mpUI = &SpriteResource::RequestTextureResource("UI", "ui_bottom");
	mUI = Point(WINDOW_WIDTH/2 - mpUI->width/2, WINDOW_HEIGHT - mpUI->height);
	mpHealth = new NSprite(WINDOW_WIDTH/2, WINDOW_HEIGHT-mpUI->height-6,
		&SpriteResource::RequestResource("UI", "ui_bottom_health"), false);
	mpLeft = new NSprite(mpHealth->GetBounds().rect.x - 15, WINDOW_HEIGHT-26,
		&SpriteResource::RequestResource("UI", "end_left"), false);
	mpRight = new NSprite(mpHealth->GetBounds().rect.x + mpUI->width + 17, WINDOW_HEIGHT-26,
		&SpriteResource::RequestResource("UI", "end_right"), false);

	mScore.x = GAME_BANNER_WIDTH;
	mScore.y = mpRedFont->pFont->getHeight("99") + 6;
	sprintf(mHiScoreStr, "%ll", ScoreIO::SaveScore::GetScores(GameScore::Instance()->GetModeString(true), 1).value);
	mHiScore.x = GAME_BOUNDS_WIDTH - max_score_width - mpRedFont->pFont->getWidth(mHiScoreStr);
	mHiScore.y = mpRedFont->pFont->getHeight("99") + 6;
	mGemOrigin = mpRedFont->pFont->getHeight("99")*2 + 14;
	mGem.x = GAME_BANNER_WIDTH + 5; mGem.y = mGemOrigin;
	mCoin.x = GAME_BANNER_WIDTH + 5; mCoin.y = mGemOrigin + mpRedFont->pFont->getHeight("99") + 3;
}

Interface::~Interface() 
{    
	printf("Interface Deleted\n");
	delete mpRedFont;
	delete mpRedFont;
	//delete icons
}

void Interface::Update(const int& rDeltaTime)
{
	UpdateIcons();
	mpInv->Update(rDeltaTime);
	sprintf(mScoreStr, "%05llu", GameScore::Instance()->GetScore());
	sprintf(mGemStr, "%03d", GameScore::Instance()->GetGemCount());
	sprintf(mCoinStr, "%03d", GameScore::Instance()->GetCoinCount());
	mScore.x = mGem.x + mpRedFont->pFont->getWidth("123456789012345") - mpRedFont->pFont->getWidth(mScoreStr);
	mpTitle->Update(rDeltaTime);
}

void Interface::Draw(SDL_Surface *pDest)
{
	mpRedFont->pFont->draw(mScore.x, mScore.y, mScoreStr);
	mpRedFont->pFont->draw(mHiScore.x, mHiScore.y, mHiScoreStr);
	mpRedFont->pFont->draw(mGem.x, mGem.y, mGemStr);
	mpRedFont->pFont->draw(mCoin.x, mCoin.y, mCoinStr);
    DrawIcons(pDest);
	Shared::DrawSurface(mUI.x, mUI.y, mpUI->pSurface, pDest);
	mpInv->Draw(pDest);
	mpTitle->Draw(pDest);
}

void Interface::UpdateIcons()
{
	mpMode->Update();
	mpPlayer->Update();
	mpHigh->Update();
	mpLeft->Update();
	mpRight->Update();
	mpHealth->Update();
}

void Interface::DrawIcons(SDL_Surface *pDest)
{
	mpMode->Draw(pDest);
	mpPlayer->Draw(pDest);
	mpHigh->Draw(pDest);
	mpLeft->Draw(pDest);
	mpRight->Draw(pDest);
	mpHealth->Draw(pDest);
}

void Interface::ActivateHub()
{
	//initialize hub positions offscreen
}