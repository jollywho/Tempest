#include "Interface.h"
#include "Engine/Spriteresource.h"
#include "Savescore.h"
#include "Gamescore.h"

Interface::Interface() 
{
	printf("Interface Created\n");
	GameScore::Instance()->ResetGame();
	warning_left_surface = Shared::load_image("Image/UI/warning_left.png");
	warning_right_surface = Shared::load_image("Image/UI/warning_right.png");
	banner_left_surface = Shared::load_image("Image/UI/ui_border_left.png");
	banner_right_surface = Shared::load_image("Image/UI/ui_border_right.png");
	banner_bottom_surface = Shared::load_image("Image/UI/ui_border_bottom.png");
	banner_bottom2_surface = Shared::load_image("Image/UI/ui_border_bottom2.png");
	green_surface = Shared::load_image("Font/bobble_green.png");
	red_surface = Shared::load_image("Font/bobble_red.png");
	font_green = new NFont(SDL_GetVideoSurface(), green_surface);
	font_red = new NFont(SDL_GetVideoSurface(), red_surface);

	SpriteResource::AddResource("UI", "lives_counter.png", 12, 24, 60, 6);
	SpriteResource::AddResource("UI", "bombs_counter.png", 24, 24, 60, 5);
	SpriteResource::AddResource("UI", "healthbar.png", 471, 16, 120, 6, true);

	for(int i=0; i<5; i++)
	{
		lives[i] = new NSprite(_G_BANNER_WIDTH + (i * 24), _G_UI_BOTTOM + 24, &SpriteResource::RequestResource("UI", "lives_counter.png"));
		bombs[i] = new NSprite(_G_BOUNDS_WIDTH - (i * 24), _G_UI_BOTTOM + 24, &SpriteResource::RequestResource("UI", "bombs_counter.png"));
	}
	hpbar = &SpriteResource::RequestResource("UI", "healthbar.png");

	hpbar_active = false;
	banner_bottom_pos.x = _G_BANNER_WIDTH;
	banner_bottom_pos.y = _G_UI_BOTTOM;

	score_title_pos.x = _WSCREEN_WIDTH/3 - font_green->getWidth("PLAYER")/2;
	score_title_pos.y = 5;
	hiscore_title_pos.x = _WSCREEN_WIDTH/2 - font_green->getWidth("HIGH SCORE")/2;
	hiscore_title_pos.y = 5;
	str_mode = GameScore::Instance()->GetMode(true);
	mode_title_pos.x = _WSCREEN_WIDTH/1.5 - font_green->getWidth(str_mode.c_str())/2;
	mode_title_pos.y = 5;
	score_pos.y = font_green->getHeight("99") + 8;
	score_origin = _WSCREEN_WIDTH/3 + font_green->getWidth("123456789")/2;
	//todo: use gamescore::getmode() NONVERBOSE
	str_hiscore << ScoreIO::SaveScore::GetScores("Normal", 1).value;
	hiscore_pos.x = _WSCREEN_WIDTH/2 + font_green->getWidth("123456789")/2 - font_green->getWidth(str_hiscore.str().c_str());
	hiscore_pos.y = font_green->getHeight("99") + 8;
	gem_origin = font_green->getHeight("99")*2 + 14;
	gem_pos.x = _G_BANNER_WIDTH + 20; gem_pos.y = gem_origin;
	coin_pos.x = _G_BANNER_WIDTH + 20; coin_pos.y = gem_origin + font_green->getHeight("99") + 3;
}

Interface::~Interface() 
{    
	printf("Interface Deleted\n");
    SDL_FreeSurface(warning_left_surface);
    SDL_FreeSurface(warning_right_surface);
    SDL_FreeSurface(banner_left_surface);
    SDL_FreeSurface(banner_right_surface);
	SDL_FreeSurface(banner_bottom_surface);
	SDL_FreeSurface(banner_bottom2_surface);
    SDL_FreeSurface(green_surface);
	SDL_FreeSurface(red_surface);

	//delete icons
	//delete font

	SpriteResource::ClearResourceDir("UI");
}

void Interface::Update(const int& iElapsedTime)
{
	UpdateIcons();
	if (hpbar_active) UpdateHealthBar();

	str_score.str("");
	str_score << GameScore::Instance()->GetScore();
	score_pos.x = score_origin - font_green->getWidth(str_score.str().c_str());

	str_gemcount.str("");
	str_gemcount << GameScore::Instance()->GetGemCount();
	str_coincount.str("");
	str_coincount << GameScore::Instance()->GetCoinCount();
}

void Interface::Draw(SDL_Surface *dest)
{
	font_green->draw(score_title_pos.x, score_title_pos.y, "PLAYER");
	font_red->draw(hiscore_title_pos.x, hiscore_title_pos.y, "HIGH SCORE");
	font_green->draw(mode_title_pos.x, mode_title_pos.y, str_mode.c_str());
	font_red->draw(score_pos.x, score_pos.y, str_score.str().c_str());
	font_green->draw(hiscore_pos.x, hiscore_pos.y, str_hiscore.str().c_str());
	font_green->draw(gem_pos.x, gem_pos.y, str_gemcount.str().c_str());
	font_green->draw(coin_pos.x, coin_pos.y, str_coincount.str().c_str());

	Shared::apply_surface(banner_bottom_pos.x,banner_bottom_pos.y,banner_bottom_surface,dest);
    DrawIcons(dest);
	Shared::apply_surface(banner_bottom_pos.x,banner_bottom_pos.y,banner_bottom2_surface,dest);
    if (hpbar_active) DrawHealthBar(dest);

	Shared::apply_surface(0,0,banner_left_surface,dest);
	Shared::apply_surface(_G_BOUNDS_WIDTH,0,banner_right_surface,dest);
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
		lives[i]->Update();
	for (int i=0; i<GameScore::Instance()->GetBombs(); i++)
		bombs[i]->Update();
}

void Interface::DrawIcons(SDL_Surface *dest)
{
	for (int i=0; i<GameScore::Instance()->GetLives(); i++)
		lives[i]->Draw(dest);
	for (int i=0; i<GameScore::Instance()->GetBombs(); i++)
		bombs[i]->Draw(dest);
}

void Interface::DrawHealthBar(SDL_Surface *dest)
{
	//healthbar_offset.y = healthbar_yVal;
}

void Interface::ActivateHealthBar()
{
    //bar_Timer.start();
    //healthbar_clip.x = 0; healthbar_clip.y = 0;
    //healthbar_clip.w = MAX_BAR_WIDTH; healthbar_clip.h = 20;
	//healthbar_yVal = -20;
}

void Interface::DeactiveHealthBar()
{
    hpbar_active = false;
}

void Interface::SetHealthbarRatio(float ratio)
{
	//ratio = % of max hp * 471
}

void Interface::ActivateHub()
{
	//init hub positions offscreen
}

void Interface::ActivateWarning()
{

}