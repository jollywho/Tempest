#include "IntroState.h"
#include "Engine/Shared.h"
#include "UI/Menu.h"
#include "Sprig.h"
#include "Engine/SpriteResource.h"
#include "UI/Decor.h"

CIntroState CIntroState::m_IntroState;

void CIntroState::Init()
{
	printf("CIntroState Init\n");
	ClearRequest();
	bg =  Shared::load_image("Image/UI/IntroBG.png");
	SpriteResource::AddResource("UI", "decor.png", 48,48,100,8);

	border_top = Shared::load_image("Image/UI/intro_border_top.png");
	border_bot = Shared::load_image("Image/UI/intro_border_bot.png");
	border_left = Shared::load_image("Image/UI/ui_border_left.png");
	border_right = Shared::load_image("Image/UI/ui_border_right.png");

	alpha = 255;

	for(int i=0; i<50; i++)
		decor_list[i] = new Decor("decor.png");

    mainMenu = new Menu();
	//
    mainMenu->AddItem(_WSCREEN_WIDTH/2, 200, "New Game");
    mainMenu->AddItem(_WSCREEN_WIDTH/2, 260, "Stage Jump");
	mainMenu->AddItem(_WSCREEN_WIDTH/2, 320, "Results");
    mainMenu->AddItem(_WSCREEN_WIDTH/2, 380, "Options");
    mainMenu->AddItem(_WSCREEN_WIDTH/2, 440, "Exit");

	bgX = 0; bgX2 = -1280;
	border_top_y = -42; border_bot_y = _WSCREEN_HEIGHT;
	border_left_x = -160; border_right_x = _WSCREEN_WIDTH;

	exiting = false; entering = true; fadeout = false; span = false;

	fade_timer.start();
}

void CIntroState::Cleanup()
{
	printf("CIntroState Cleanup\n");
    delete mainMenu;
	for(int i=0; i<50; i++)
		delete decor_list[i];
	SDL_FreeSurface(bg);

	SDL_FreeSurface(border_top);
	SDL_FreeSurface(border_bot);
	SDL_FreeSurface(border_left);
	SDL_FreeSurface(border_right);
}

void CIntroState::Return()
{
	printf("CIntroState Return\n");
	entering = true;
	alpha = 255;
	//todo: reset menu index
}

void CIntroState::CheckKeys(const KeyStruct& keys)
{
	if (exiting) return;
	if (keys.z)
	{
		mainMenu->Select();
		entering = false;
		exiting = true;
		if (mainMenu->GetIndex() == 1) { span = true; fadeout = true; }
		if (mainMenu->GetIndex() == 2) { fadeout = true; }
		if (mainMenu->GetIndex() == 4) { fadeout = true; }
	}
	if (keys.down) mainMenu->SetIndex(1);
	else if (keys.up) mainMenu->SetIndex(-1);
	else mainMenu->Release();	
}

void CIntroState::MenuAction()
{
	if (mainMenu->GetIndex() == 1) ChangeState(Play);
	//if (mainMenu->GetIndex() == 2) RequestState(Poll);
	if (mainMenu->GetIndex() == 2) { PushMenu(Play); exiting = false; }
	if (mainMenu->GetIndex() == 4) ChangeState(Option);
}

void CIntroState::Update(const int& iElapsedTime) 
{
	mainMenu->Update(iElapsedTime, alpha);
	for(int i=0; i<50; i++)
		decor_list[i]->Update(iElapsedTime);

	bgX += 1; bgX2 += 1;
	if (bgX > _WSCREEN_WIDTH) 
		bgX = bgX2 - 1280;
	if (bgX2 > _WSCREEN_WIDTH) 
		bgX2 = bgX - 1280;

	if (entering)
	{
		if (border_top_y < 0)
		{
			border_top_y+=2;
			border_bot_y-=2;
		}
		else if (alpha > 0) 
		{
			if (fade_timer.get_ticks() > 10) 
			{
				alpha-=5;
				fade_timer.start(); 
			} 
		}
		else
			entering = false;
	}
	if (exiting)
	{
		if (span && border_left_x < 0)
		{
			border_left_x+=2;
			border_right_x-=2;
			border_top_y-=2;
			border_bot_y+=2;
		}
		else if (fadeout && alpha < 255) 
		{
			if (fade_timer.get_ticks() > 10) 
			{
				alpha+=5;
				fade_timer.start(); 
			} 
		}
		else
			MenuAction();
	}
}

void CIntroState::Draw(SDL_Surface* dest) 
{
	Shared::apply_surface((int)bgX,0,bg,dest);
	Shared::apply_surface((int)bgX2,0,bg,dest);

	for(int i=0; i<50; i++)
		decor_list[i]->Draw(dest);

	mainMenu->Draw(dest);
	SPG_RectFilledBlend(dest,0,0,_WSCREEN_WIDTH,_WSCREEN_HEIGHT, 0, alpha);

	Shared::apply_surface(0, border_top_y, border_top, dest);
	Shared::apply_surface(0, border_bot_y, border_bot, dest);

	Shared::apply_surface(border_left_x, 0, border_left, dest);
	Shared::apply_surface(border_right_x, 0, border_right, dest);
}
