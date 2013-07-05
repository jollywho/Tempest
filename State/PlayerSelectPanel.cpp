#include "PlayerSelectPanel.h"
#include "UI/NSprite.h"
#include "Game/GameScore.h"
#include "UI/Menu.h"
#include "Engine/SpriteResource.h"
#include "Weapon/MType.h"
#include "Engine/ResourceLoader.h"

PlayerSelectPanel::PlayerSelectPanel()
{
	printf("-PlayerSelectPanel Created-\n");
	mBack = false; mForward = false;
	ResourceLoader::ReadFile("Player");
	mpPlayer = new NSprite(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, &SpriteResource::RequestResource("Player", "angel_1.png"));
	mpTitle = Shared::LoadImage("Image/UI/select_player_title.png");
	mIndex = 1;
}

PlayerSelectPanel::~PlayerSelectPanel()
{
	printf("-PlayerSelectPanel Deleted-\n");
	delete mpPlayer;
	SDL_FreeSurface(mpTitle);
	for (auto it = mpBulletList.begin(); it != mpBulletList.end();) {
		delete (*it);
		it++; }
	mpBulletList.clear();
}

void PlayerSelectPanel::KeyInput(const KeyStruct& rKeys)
{
	if (rKeys.esc || rKeys.x) mBack = true;
	if (rKeys.z)
	{
		mForward = true;
	}
	if (rKeys.down) mIndex++;
	else if (rKeys.up) mIndex--;
	if (mIndex > 3) mIndex = 1;
	if (mIndex < 1) mIndex = 3;

	if (rKeys.down || rKeys.up)
	{
		std::stringstream angel_name;
		angel_name << "angel_" << mIndex << ".png";
		delete mpPlayer;
		mpPlayer = new NSprite(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 
			&SpriteResource::RequestResource("Player", angel_name.str()));
	}
}

void PlayerSelectPanel::Update(const int& rDeltaTime)
{
	mpPlayer->Update();
	for (auto it = mpBulletList.begin(); it != mpBulletList.end();)
	{
		(*it)->Update(rDeltaTime);
		if ((*it)->RequestDelete())
		{
			delete (*it);
			it = mpBulletList.erase(it);	
		}
		else
		{
			it++;
		}
	}
}

void PlayerSelectPanel::Draw(SDL_Surface *pDest)
{
	mpPlayer->Draw(pDest);
}

void PlayerSelectPanel::DrawTop(SDL_Surface *pDest)
{
	if (!mForward)
		Shared::DrawSurface(0,0, mpTitle, pDest);
}