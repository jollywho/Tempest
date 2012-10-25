#include "OptionMenu.h"
#include "Menu.h"
#include "Engine/SFX.h"

OptionMenu::OptionMenu()
{
	exit_ready = false;

	//load config from file
	SFX::AddSoundResource("sound_test.wav");
	selector = Shared::load_image("Image/UI/SoundSelector.png");
	frame = Shared::load_image("Image/UI/SoundFrame.png");

    char* msg1 = "BGM";
    char* msg2 = "SFX";
	char* msg3 = "Mode";

	char* msg4 = "Attack";
	char* msg5 = "Bomb";
	char* msg6 = "Focus";

    char* msg7 = "Defaults";
    char* msg8 = "Return";
	menu = new Menu();

	Point align = menu->GetFontSize(msg1);

	int menuheight = _WSCREEN_HEIGHT/2 - (align.y * 8)/2 - 84;

	align_x = _WSCREEN_WIDTH/2 - align.x*2.5;
	bgm_y =  menuheight + (0*60);
    menu->AddItem(align_x, bgm_y, msg1);

	align_x = align_x + align.x/2;

	bgmframe_x = _WSCREEN_WIDTH/2 - align.x/4;
	bgmframe_y = bgm_y + (align.y/2-10);
	bgmselector_y = bgmframe_y + (20/2-32/2);
	
	align = menu->GetFontSize(msg2);

	fx_y = menuheight + (1*60);
    menu->AddItem(align_x - align.x/2, fx_y, msg2);
	fxframe_x = bgmframe_x;
	fxframe_y = fx_y + (align.y/2-10);
	fxselector_y = fxframe_y + (20/2-32/2);

	fxselector_x = fxframe_x + (((double)SFX::SetFX(0)/MIX_MAX_VOLUME)*235);
	bgmselector_x = bgmframe_x + (((double)SFX::SetBGM(0)/MIX_MAX_VOLUME)*235);

	align = menu->GetFontSize(msg3);
    menu->AddItem(align_x - align.x/2, menuheight + (2*60), msg3);
    menu->AddItem(align_x - align.x/2, menuheight + (3*60), msg4);
	align = menu->GetFontSize(msg5);
    menu->AddItem(align_x - align.x/2, menuheight + (4*60), msg5);
	align = menu->GetFontSize(msg6);
    menu->AddItem(align_x - align.x/2, menuheight + (5*60), msg6);
	align = menu->GetFontSize(msg7);
    menu->AddItem(align_x - align.x/2, menuheight + (6*60), msg7);
	align = menu->GetFontSize(msg7);
    menu->AddItem(align_x - align.x/2, menuheight + (7*60), msg8);
}

OptionMenu::~OptionMenu()
{
	delete menu;
}

//void OptionMenu::Handle_input(SDL_Event event)
//{
//	menu->Handle_input(event);
//    if( event.type == SDL_KEYDOWN )
//    {
//		switch(event.key.keysym.sym)
//		{
//		case SDLK_z:
//			break;
//		case SDLK_LEFT:
//			switch(menu->selectedIndex)
//			{
//			case 1:
//				bgmselector_x = bgmframe_x + (((double)SFX::SetBGM(-1)/MIX_MAX_VOLUME)*235);
//				break;
//			case 2:
//				fxselector_x = fxframe_x + (((double)SFX::SetFX(-1)/MIX_MAX_VOLUME)*235);
//				break;
//			}
//			break;
//		case SDLK_RIGHT:
//			switch(menu->selectedIndex)
//			{
//			case 1:
//				bgmselector_x = bgmframe_x + (((double)SFX::SetBGM(1)/MIX_MAX_VOLUME)*235);
//				break;
//			case 2:
//				fxselector_x = fxframe_x + (((double)SFX::SetFX(1)/MIX_MAX_VOLUME)*235);
//				break;
//			}
//			break;
//		}
//    }
//}

void OptionMenu::Update(Uint32 deltaTicks, int alpha)
{
	menu->Update(deltaTicks, alpha);
	//if (menu->Ready() && menu->GetIndex() == menu->maxItems)
	//	exit_ready = true;
	//else if (menu->Ready()) 
	//	menu->Reset();
	if (menu->GetIndex() == 2 && !Mix_Playing(2))
		SFX::PlayChannelResource("sound_test.wav", 2);

}

void OptionMenu::Draw(SDL_Surface *dest)
{
	menu->Draw(dest);
	Shared::apply_surface(bgmframe_x,bgmframe_y,frame,dest);
	Shared::apply_surface(bgmselector_x,bgmselector_y,selector,dest);

	Shared::apply_surface(fxframe_x,fxframe_y,frame,dest);
	Shared::apply_surface(fxselector_x,fxselector_y,selector,dest);
}