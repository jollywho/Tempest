#include "SelectPanel.h"
#include "playstate.h"
#include "Player/Player.h"
#include "Game/GameScore.h"
#include "UI/Menu.h"

SelectPanel::SelectPanel()
{
	printf("-SelectPanel Created-\n");
	mBack = false; mForward = false;

	charselect = false;
	grow = false;
	shrink = false;
	swap = false;
	click = false;
	modeTail = Shared::LoadImage("Image/UI/SelectModeTail.png");
	modeFrame = Shared::LoadImage("Image/UI/SelectModeBanner.png");

	SDL_Color color =   {49, 38, 32};
    SDL_Color color2 =  {200, 160, 88};
    SDL_Color selCol =  {231, 230, 226};
	int w, h;
    char* msg1 = "Normal"; char* msg2 = "Ultra"; char* msg3 = "Insane";
	char* type1 = "M-Type"; char* type2 = "S-Type"; char* type3 = "R-Type";
	menu = new Menu();
	wpnMenu = new Menu();
	//bannerRect.x = 0; bannerRect.y = 0;
	//bannerRect.h = 270; bannerRect.w = 256;
	//banner_x = _WSCREEN_WIDTH/2-256/2;
	//banner_y = _WSCREEN_HEIGHT/2-300/2;
	//banner_tail = banner_y + 270;
	//int menu_y = banner_y + (.25 * 300);
	//
	//TTF_SizeText(menu->menuFont, msg1, &w, &h);
	//menu->AddItem(new MenuItem(_WSCREEN_WIDTH/2 - w/2, menu_y, msg1, 1, color, color2, selCol));
	//TTF_SizeText(menu->menuFont, msg2, &w, &h);
	//menu->AddItem(new MenuItem(_WSCREEN_WIDTH/2 - w/2, menu_y + 60, msg2, 2, color, color2, selCol));
	//TTF_SizeText(menu->menuFont, msg3, &w, &h);
	//menu->AddItem(new MenuItem(_WSCREEN_WIDTH/2 - w/2, menu_y + 120, msg3, 3, color, color2, selCol));
	//
	//TTF_SizeText(menu->menuFont, type1, &w, &h);
	//wpnMenu->AddItem(new MenuItem(_WSCREEN_WIDTH/2 - w/2, menu_y, type1, 1, color, color2, selCol));
	//TTF_SizeText(menu->menuFont, type2, &w, &h);
	//wpnMenu->AddItem(new MenuItem(_WSCREEN_WIDTH/2 - w/2, menu_y + 60, type2, 2, color, color2, selCol));
	//TTF_SizeText(menu->menuFont, type3, &w, &h);
	//wpnMenu->AddItem(new MenuItem(_WSCREEN_WIDTH/2 - w/2, menu_y + 120, type3, 3, color, color2, selCol));


	//pl = Shared::load_image("Image/UI/Chibi_Angel.png");
	//Shared::setFrames(pl_clips,3,80,60);

	//wpn1 = new MType(); wpn1->SetLevel(4); wpn1->SetPos(128, 380, 0);
	//wpn2 = new SType(); wpn2->SetLevel(4); wpn2->SetPos(128, 380, 0);
	//SDL_Rect tempbounds =  {0, _GSCREEN_HEIGHT, banner_x+256, 0} ;
	//PlayerBullet::BoundRect = tempbounds;
	//stopTimer.start();
}

SelectPanel::~SelectPanel()
{
	printf("-SelectPanel Deleted-\n");
	//for (auto it = pl_bulletlist.begin(); it != pl_bulletlist.end();) {
	//	delete (*it);
	//	it++; }
	//pl_bulletlist.clear();
	//SDL_FreeSurface(pl);
	//delete menu;
	//delete wpnMenu;
	//delete wpn1;
	//delete wpn2;
	//SDL_FreeSurface(modeTail);
	//SDL_FreeSurface(modeFrame);
}

void SelectPanel::KeyInput(const KeyStruct& rKeys)
{
	if (rKeys.x)
		mBack = true;
	if (rKeys.z)
		mForward = true;
}

void SelectPanel::Update(const int& rDeltaTime)
{

}

void SelectPanel::Draw(SDL_Surface *pDest)
{

}