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
	mpGreenSurface = Shared::LoadImage("Font/bobble_green.png");
	mpRedSurface = Shared::LoadImage("Font/bobble_red.png");
	mpGreenFont = new NFont(SDL_GetVideoSurface(), mpGreenSurface);
	mpRedFont = new NFont(SDL_GetVideoSurface(), mpRedSurface);

	for(int i=0; i<GameScore::MAX_BOMBS; i++)
	{
		mpLives[i] = new NSprite(GAME_BANNER_WIDTH + (i * 24), GAME_UI_BOTTOM + 24, 
			&SpriteResource::RequestResource("UI", "lives_counter.png"));
		mpBombs[i] = new NSprite(GAME_BOUNDS_WIDTH - (i * 24), GAME_UI_BOTTOM + 24, 
			&SpriteResource::RequestResource("UI", "bombs_counter.png"));
	}
	mpMode = new NSprite(GAME_UI_MODE_X, GAME_UI_MODE_Y, 
		&SpriteResource::RequestResource("UI", GameScore::Instance()->GetModeString() + ".png"), false, true);
	mpHpBar = &SpriteResource::RequestResource("UI", "healthbar.png");

	mHpBarActive = false;
	mBannerBot.x = GAME_BANNER_WIDTH;
	mBannerBot.y = GAME_UI_BOTTOM;

	mScoreTitle.x = WINDOW_WIDTH/3 - mpRedFont->getWidth("PLAYER")/2;
	mScoreTitle.y = 5;
	mHiScoreTitle.x = WINDOW_WIDTH/2 - mpRedFont->getWidth("HIGH SCORE")/2;
	mHiScoreTitle.y = 5;
	mScore.y = mpRedFont->getHeight("99") + 8;
	mScoreOrigin = WINDOW_WIDTH/3 + mpRedFont->getWidth("123456789")/2;
	//todo: use gamescore::getmode() NONVERBOSE
	mHiScoreStr << ScoreIO::SaveScore::GetScores("Normal", 1).value;
	mHiScore.x = WINDOW_WIDTH/2 + mpRedFont->getWidth("123456789")/2 - mpRedFont->getWidth(mHiScoreStr.str().c_str());
	mHiScore.y = mpRedFont->getHeight("99") + 8;
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
    SDL_FreeSurface(mpGreenSurface);
	SDL_FreeSurface(mpRedSurface);
	delete mpGreenFont;
	delete mpRedFont;
	//delete icons

	
}

void Interface::Update(const int& rDeltaTime)
{
	UpdateIcons();
	if (mHpBarActive) UpdateHealthBar();

	mScoreStr.str("");
	mScoreStr << GameScore::Instance()->GetScore();
	mScore.x = mScoreOrigin - mpGreenFont->getWidth(mScoreStr.str().c_str());

	mGemCountStr.str("");
	mGemCountStr << GameScore::Instance()->GetGemCount();
	mCoinCountStr.str("");
	mCoinCountStr << GameScore::Instance()->GetCoinCount();
}

void Interface::Draw(SDL_Surface *pDest)
{
	mpGreenFont->draw(mScoreTitle.x, mScoreTitle.y, "PLAYER");
	mpRedFont->draw(mHiScoreTitle.x, mHiScoreTitle.y, "HIGH SCORE");
	mpRedFont->draw(mScore.x, mScore.y, mScoreStr.str().c_str());
	mpGreenFont->draw(mHiScore.x, mHiScore.y, mHiScoreStr.str().c_str());
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
}

void Interface::DrawIcons(SDL_Surface *pDest)
{
	for (int i=0; i<GameScore::Instance()->GetLives(); i++)
		mpLives[i]->Draw(pDest);
	for (int i=0; i<GameScore::Instance()->GetBombs(); i++)
		mpBombs[i]->Draw(pDest);
	mpMode->Draw(pDest);
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