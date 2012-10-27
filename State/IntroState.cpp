#include "IntroState.h"
#include "Engine/Shared.h"
#include "UI/Menu.h"
#include "Sprig.h"
#include "Engine/SpriteResource.h"
#include "UI/Decor.h"

CIntroState CIntroState::m_IntroState;

void CIntroState::Init()
{
	ClearRequest();
	bg =  Shared::load_image("Image/UI/IntroBG.png");
	SpriteResource::AddResource("UI", "decor.png", 48,48,100,8);
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

	fade_timer.start();
	printf("CIntroState Init\n");
}

void CIntroState::Cleanup()
{
	printf("CIntroState Cleanup\n");
    delete mainMenu;
	for(int i=0; i<50; i++)
		delete decor_list[i];
	SDL_FreeSurface(bg);
}

void CIntroState::Pause()
{
	printf("CIntroState Pause\n");
}

void CIntroState::Resume()
{
	printf("CIntroState Resume\n");
}

void CIntroState::CheckKeys(const KeyStruct& keys)
{
	if (keys.z)
		{
			mainMenu->Select(); 
			if (mainMenu->GetIndex() == 1) RequestState(Play);
			if (mainMenu->GetIndex() == 4) RequestState(Option);
		}
	if (keys.down) mainMenu->SetIndex(1);
	else if (keys.up) mainMenu->SetIndex(-1);
	else mainMenu->Release();	
}

void CIntroState::Update(const int& iElapsedTime) 
{
	mainMenu->Update(iElapsedTime, alpha);
	for(int i=0; i<50; i++)
		decor_list[i]->Update(iElapsedTime);
	if (alpha > 0) {
		if (fade_timer.get_ticks() > 10) {
			alpha-=2;
			fade_timer.start(); } }

	bgX += 1; bgX2 += 1;
	if (bgX > _WSCREEN_WIDTH) 
		bgX = bgX2 - 1280;
	if (bgX2 > _WSCREEN_WIDTH) 
		bgX2 = bgX - 1280;
}

void CIntroState::Draw(SDL_Surface* dest) 
{
	Shared::apply_surface((int)bgX,0,bg,dest);
	Shared::apply_surface((int)bgX2,0,bg,dest);

	for(int i=0; i<50; i++)
		decor_list[i]->Draw(dest);

	mainMenu->Draw(dest);

	if ( alpha > 0 )
		SPG_RectFilledBlend(dest,0,0,_WSCREEN_WIDTH,_WSCREEN_HEIGHT, 0, alpha);
}
