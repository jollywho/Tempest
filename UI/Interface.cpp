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
��*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
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
	int max_score_width = mpRedFont->pFont->getWidth("123456789012345") / 2;
	mpMode = new NSprite(WINDOW_WIDTH / 2, GAME_UI_MODE_Y, 
		&SpriteResource::RequestResource("UI", GameScore::Instance()->GetModeString()), false, true);
	mpPlayer = new NSprite(WINDOW_WIDTH * 0.25 - max_score_width / 2, GAME_UI_MODE_Y, 
		&SpriteResource::RequestResource("UI", "player_title"), false, true);
	mpHigh = new NSprite(WINDOW_WIDTH * 0.75 + max_score_width / 2, GAME_UI_MODE_Y, 
		&SpriteResource::RequestResource("UI", "high_title"), false);

	mpMana = new HealthBar("ui_left", "mana_left", Point(0, WINDOW_HEIGHT), true, true);
	mpBomb = new HealthBar("ui_right", "mana_right", Point(WINDOW_WIDTH, WINDOW_HEIGHT), true, false);
	mpHealth = new HealthBar("ui_bottom", "health_left", Point(890, WINDOW_HEIGHT), true, true);
	mpShield = new HealthBar("ui_bottom", "shield_right", Point(733, WINDOW_HEIGHT), false, true);

	mpMana->SetRecRate(1);
	mpBomb->SetRecRate(1);

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

void Interface::Draw(SDL_Surface *pdest)
{
	mpHealth->Draw(pdest);
	mpShield->Draw(pdest);
	mpMana->Draw(pdest);
	mpBomb->Draw(pdest);
	mpRedFont->pFont->draw(mScore.x, mScore.y, mScoreStr);
	mpRedFont->pFont->draw(mHiScore.x, mHiScore.y, mHiScoreStr);
	mpRedFont->pFont->draw(mGem.x, mGem.y, mGemStr);
	mpRedFont->pFont->draw(mCoin.x, mCoin.y, mCoinStr);
    DrawIcons(pdest);
	mpInv->Draw(pdest);
	mpTitle->Draw(pdest);
}

void Interface::UpdateIcons()
{
	mpHealth->Update();
	mpShield->Update();
	mpMana->Update();
	mpBomb->Update();
	mpMode->Update();
	mpPlayer->Update();
	mpHigh->Update();
}

void Interface::DrawIcons(SDL_Surface *pdest)
{
	mpHealth->Draw(pdest);
	mpShield->Draw(pdest);
	mpMana->Draw(pdest);
	mpBomb->Draw(pdest);
	mpMode->Draw(pdest);
	mpPlayer->Draw(pdest);
	mpHigh->Draw(pdest);
}

void Interface::ActivateHub()
{
	//initialize hub positions offscreen
}

void Interface::SetHealth(int val)
{
	if (mpShield->GetVal() > 0)
		mpShield->SetValue(val);
	else
		mpHealth->SetValue(val);
}

bool Interface::SetMana(int val)
{
	if (mpMana->GetVal() > 0)
	{
		mpMana->SetValue(val);
		return true;
	}
	else
		return false;
}

bool Interface::SetBomb(int val)
{
	if (mpBomb->GetVal() > 0)
	{
		mpBomb->SetRecRate(0);
		mpBomb->SetValue(val);
		return true;
	}
	else
	{
		mpBomb->SetRecRate(1);
		return false;
	}
}

float Interface::GetBomb()
{
	return mpBomb->GetPercent();
}

void Interface::SetMaxMana(int val) { mpMana->SetMaxVal(val); }
void Interface::SetMaxBomb(int val) { mpBomb->SetMaxVal(val); }