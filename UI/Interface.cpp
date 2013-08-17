#include "Interface.h"
#include "Engine/SpriteResource.h"
#include "Engine/FontResource.h"
#include "Game/Savescore.h"
#include "NSprite.h"
#include "Shop/Inventory.h"
#include "Title.h"
#include "HealthBar.h"

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

	mpManaLeft = new HealthBar("ui_left", "mana_left", Point(0, WINDOW_HEIGHT), true);
	mpManaRight = new HealthBar("ui_right", "mana_right", Point(WINDOW_WIDTH, WINDOW_HEIGHT), true);
	mpHealth = new HealthBar("ui_bottom", "health_left", Point(890, WINDOW_HEIGHT), true);
	mpShield = new HealthBar("ui_bottom", "shield_right", Point(890, WINDOW_HEIGHT), false);

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
	mpHealth->Draw(pDest);
	mpShield->Draw(pDest);
	mpManaLeft->Draw(pDest);
	mpManaRight->Draw(pDest);
	mpRedFont->pFont->draw(mScore.x, mScore.y, mScoreStr);
	mpRedFont->pFont->draw(mHiScore.x, mHiScore.y, mHiScoreStr);
	mpRedFont->pFont->draw(mGem.x, mGem.y, mGemStr);
	mpRedFont->pFont->draw(mCoin.x, mCoin.y, mCoinStr);
    DrawIcons(pDest);
	mpInv->Draw(pDest);
	mpTitle->Draw(pDest);
}

void Interface::UpdateIcons()
{
	mpHealth->Update();
	mpShield->Update();
	mpManaLeft->Update();
	mpManaRight->Update();
	mpMode->Update();
	mpPlayer->Update();
	mpHigh->Update();
}

void Interface::DrawIcons(SDL_Surface *pDest)
{
	mpHealth->Draw(pDest);
	mpShield->Draw(pDest);
	mpManaLeft->Draw(pDest);
	mpManaRight->Draw(pDest);
	mpMode->Draw(pDest);
	mpPlayer->Draw(pDest);
	mpHigh->Draw(pDest);
}

void Interface::ActivateHub()
{
	//initialize hub positions offscreen
}