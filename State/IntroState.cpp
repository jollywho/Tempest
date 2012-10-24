#include "IntroState.h"
#include "Engine/Shared.h"
#include "UI/Menu.h"
#include "Sprig.h"

CIntroState CIntroState::m_IntroState;

void CIntroState::Init()
{
	bg =  Shared::load_image("Image/UI/IntroBG.png");

	alpha = 255;

    mainMenu = new Menu();
	//
    mainMenu->AddItem(74, 320, "New Game");
    mainMenu->AddItem(70, 380, "Level Jump");
    mainMenu->AddItem(92, 440, "Options");
    mainMenu->AddItem(115, 500, "Exit");


	printf("CIntroState Init\n");
}

void CIntroState::Cleanup()
{
    //delete mainMenu;
	SDL_FreeSurface(bg);
	//SDL_FreeSurface(fader);
	//printf("CIntroState Cleanup\n");
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
	if (keys.down)	mainMenu->SetIndex(-1);
	if (keys.up)	mainMenu->SetIndex(1);
}
//void CIntroState::HandleEvents(CEngine* game)
//{
//	//SDL_Event event;
//	//
//	//if (SDL_PollEvent(&event)) {
//    //    mainMenu->Handle_input(event);
//	//	switch (event.type) {
//	//		case SDL_QUIT:
//	//			game->Quit();
//	//			break;
//	//
//	//		case SDL_KEYDOWN:
//	//			switch (event.key.keysym.sym)
//    //            {
//	//				case SDLK_z:
//    //                    {
//    //                    if (mainMenu->selectedIndex == 1)
//	//					    game->ChangeState( CSelectState::Instance() );
//    //                    else if (mainMenu->selectedIndex == 3)
//    //                        game->PushState( CMenuState::Instance() );
//    //                    else if (mainMenu->selectedIndex == 4)
//    //                        game->Quit();
//    //                    }
//	//					break;
//    //                case SDLK_F11:
//    //                    game->Fullscreen();
//    //                    break;
//	//			}
//	//			break;
//	//	}
//	//}
//}

void CIntroState::Update(const int& iElapsedTime) 
{
	mainMenu->Update(iElapsedTime, alpha);
	if (alpha > 0)
		alpha -= iElapsedTime/1000.f;
}

void CIntroState::Draw(SDL_Surface* dest) 
{
	SDL_BlitSurface(bg, NULL, dest, NULL);
	mainMenu->Draw(dest);

	if ( alpha > 0 )
		SPG_RectFilledBlend(dest,0,0,_WSCREEN_WIDTH,_WSCREEN_HEIGHT, 0, alpha);
}
