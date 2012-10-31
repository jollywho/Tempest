#include "Interface.h"
#include "Engine/Spriteresource.h"
#include "Savescore.h"
#include "Gamescore.h"

Interface::Interface() 
{
	printf("Interface Created\n");
	GameScore::Instance()->ResetGame();
	mpWarningLeftSurface = Shared::LoadImage("Image/UI/warning_left.png");
	mpWarningRightSurface = Shared::LoadImage("Image/UI/warning_right.png");
	mpBannerLeftSurface = Shared::LoadImage("Image/UI/ui_border_left.png");
	mpBannerRightSurface = Shared::LoadImage("Image/UI/ui_border_right.png");
	mpBannerBotSurface = Shared::LoadImage("Image/UI/ui_border_bottom.png");
	mpBannerBot2Surface = Shared::LoadImage("Image/UI/ui_border_bottom2.png");
	mpRedSurface = Shared::LoadImage("Font/GoldMistral.png");
	mpRedFont = new NFont(SDL_GetVideoSurface(), mpRedSurface);
	mpRedFont->setSpacing(2);

	for(int i=0; i<GameScore::MAX_BOMBS; i++)
	{
		mpLives[i] = new NSprite(GAME_BANNER_WIDTH + (i * 24), GAME_UI_BOTTOM + 24, 
			&SpriteResource::RequestResource("UI", "lives_counter.png"));
		mpBombs[i] = new NSprite(GAME_BOUNDS_WIDTH - (i * 24), GAME_UI_BOTTOM + 24, 
			&SpriteResource::RequestResource("UI", "bombs_counter.png"));
	}
	mpMode = new NSprite(WINDOW_WIDTH/2, GAME_UI_MODE_Y, 
		&SpriteResource::RequestResource("UI", GameScore::Instance()->GetModeString() + ".png"), false, true);
	mpPlayer = new NSprite(WINDOW_WIDTH/3 - 20, GAME_UI_MODE_Y, 
		&SpriteResource::RequestResource("UI", "player_title.png"), false, true);
	mpHigh = new NSprite(WINDOW_WIDTH/1.5 + 20, GAME_UI_MODE_Y, 
		&SpriteResource::RequestResource("UI", "high_title.png"), false);
	mpHpBar = &SpriteResource::RequestResource("UI", "healthbar.png");

	mHpBarActive = false;
	mBannerBot.x = GAME_BANNER_WIDTH;
	mBannerBot.y = GAME_UI_BOTTOM;

	int max_score_width = mpRedFont->getWidth("1234567899")/2;

	mScore.x = GAME_BANNER_WIDTH + 20;
	mScore.y = mpRedFont->getHeight("99") + 6;

	mHiScoreStr << ScoreIO::SaveScore::GetScores(GameScore::Instance()->GetModeString(true), 1).value;
	mHiScore.x = GAME_BOUNDS_WIDTH - 20 - max_score_width - mpRedFont->getWidth(mHiScoreStr.str().c_str())/2;

	mHiScore.y = mpRedFont->getHeight("99") + 6;
	mGemOrigin = mpRedFont->getHeight("99")*2 + 14;
	mGem.x = GAME_BANNER_WIDTH + 20; mGem.y = mGemOrigin;
	mCoin.x = GAME_BANNER_WIDTH + 20; mCoin.y = mGemOrigin + mpRedFont->getHeight("99") + 3;
}

Interface::~Interface() 
{    
	printf("Interface Deleted\n");
    SDL_FreeSurface(mpWarningLeftSurface);
    SDL_FreeSurface(mpWarningRightSurface);
    SDL_FreeSurface(mpBannerLeftSurface);
    SDL_FreeSurface(mpBannerRightSurface);
	SDL_FreeSurface(mpBannerBotSurface);
	SDL_FreeSurface(mpBannerBot2Surface);
	SDL_FreeSurface(mpRedSurface);
	delete mpRedFont;
	//delete icons

	
}

void Interface::Update(const int& rDeltaTime)
{
	UpdateIcons();
	if (mHpBarActive) UpdateHealthBar();

	mScoreStr.str("");
	mScoreStr << GameScore::Instance()->GetScore();
	mScore.x = mGem.x + mpRedFont->getWidth("123456789") - mpRedFont->getWidth(mScoreStr.str().c_str())/2;

	mGemCountStr.str("");
	mGemCountStr << GameScore::Instance()->GetGemCount();
	mCoinCountStr.str("");
	mCoinCountStr << GameScore::Instance()->GetCoinCount();
}

void Interface::Draw(SDL_Surface *pDest)
{
	mpRedFont->draw(mScore.x, mScore.y, mScoreStr.str().c_str());
	mpRedFont->draw(mHiScore.x, mHiScore.y, mHiScoreStr.str().c_str());
	mpRedFont->draw(mGem.x, mGem.y, mGemCountStr.str().c_str());
	mpRedFont->draw(mCoin.x, mCoin.y, mCoinCountStr.str().c_str());

	Shared::DrawSurface(mBannerBot.x, mBannerBot.y, mpBannerBotSurface, pDest);
    DrawIcons(pDest);
	Shared::DrawSurface(mBannerBot.x, mBannerBot.y, mpBannerBot2Surface, pDest);
    if (mHpBarActive) DrawHealthBar(pDest);

	Shared::DrawSurface(0, 0, mpBannerLeftSurface, pDest);
	Shared::DrawSurface(GAME_BOUNDS_WIDTH, 0, mpBannerRightSurface, pDest);
}

void Interface::UpdateHealthBar()
{
	//if unlocked && posy < hpbar_dest
		//if timer
			//move barPos
			//move scoresPos
	//shared::checkclip
}

void Interface::UpdateIcons()
{
	for (int i=0; i<GameScore::Instance()->GetLives(); i++)
		mpLives[i]->Update();
	for (int i=0; i<GameScore::Instance()->GetBombs(); i++)
		mpBombs[i]->Update();
	mpMode->Update();
	mpPlayer->Update();
	mpHigh->Update();
}

void Interface::DrawIcons(SDL_Surface *pDest)
{
	for (int i=0; i<GameScore::Instance()->GetLives(); i++)
		mpLives[i]->Draw(pDest);
	for (int i=0; i<GameScore::Instance()->GetBombs(); i++)
		mpBombs[i]->Draw(pDest);
	mpMode->Draw(pDest);
	mpPlayer->Draw(pDest);
	mpHigh->Draw(pDest);
}

void Interface::DrawHealthBar(SDL_Surface *pDest)
{
	//healthfset.y = healthbar_mY;
}

void Interface::ActivateHealthBar()
{
    //bar_Timer.Start();
    //healthbar_clip.x = 0; healthbar_clip.y = 0;
    //healthbar_clip.w = MAX_BAR_WIDTH; healthbar_clip.h = 20;
	//healthbar_mY = -20;
}

void Interface::DeactiveHealthBar()
{
    mHpBarActive = false;
}

void Interface::SetHealthbarRatio(float ratio)
{
	//ratio = % of max hp * 471
}

void Interface::ActivateHub()
{
	//initialize hub positions offscreen
}

void Interface::ActivateWarning()
{

}