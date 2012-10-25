#include "Interface.h"
#include "Engine/Spriteresource.h"
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

    str_score.str("");
	str_score << GameScore::Instance()->GetScore();

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
}

void Interface::Draw(SDL_Surface *dest)
{
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
	for (int i=0; i<5; i++)
	{
		lives[i]->Update();
		bombs[i]->Update();
	}
}

void Interface::DrawIcons(SDL_Surface *dest)
{
	for (int i=0; i<5; i++)
	{
		lives[i]->Draw(dest);
		bombs[i]->Draw(dest);
	}
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