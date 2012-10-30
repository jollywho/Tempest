#include "Item.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "Game/Interface.h"
#include "Game/Camera.h"
#include "Player/Player.h"

SDL_Surface* Item::smpPickupFrameInfo;

Item::Item(int x, int y, int value, char* id)
{
	mpInfo = &SpriteResource::RequestResource("Items", id);
    mDelete = false; pickedup = false; received = false;
    val = 25; mClip = 0;
	mX = x - mpInfo->width/2;
    mY = y - mpInfo->height/2 - Camera::CameraY2();
    mOffset.x = mX;
    mOffset.y = mY;
    mOffset.w = mpInfo->width;
    mOffset.h = mpInfo->height;
	mClipTimer.Start();
	mDurationTimer.Start();
}

Item::~Item() {}

void Item::SetBonus(int val)
{
	
}

void Item::Init()
{
	printf("Item initialize!\n");
	SpriteResource::AddResource("Items", "Gem.png", 32, 32, 60, 8);
	SpriteResource::AddResource("Items", "Coin.png", 32, 32, 60, 6);
	SpriteResource::AddResource("Items", "bombup.png", 48, 48, 60, 5);
	SpriteResource::AddResource("Items", "Powerup.png", 64, 64, 60, 4);
	SpriteResource::AddResource("Items", "Chest.png", 34, 40, 160, 4);
	SpriteResource::AddResource("Items", "Quartz.png", 32, 44, 30, 7);

	SpriteResource::AddResource("Items", "bombup_received.png", 70, 15, 60, 5, true);
	SpriteResource::AddResource("Items", "Powerup_Received.png", 86, 15, 60, 6, true);
	smpPickupFrameInfo = Shared::LoadImage("Image/Items/Receive_Frame.png");

	SFX::AddSoundResource("damage.wav");
	SFX::AddSoundResource("pickup.wav");
	SFX::AddSoundResource("powerup_pickup.wav");
	SFX::AddSoundResource("bombup_pickup.wav");
	SFX::AddSoundResource("gem_pickup.wav");
	SFX::AddSoundResource("coin_pickup.wav");
	SFX::AddSoundResource("tick.wav");
}

void Item::Cleanup()
{
	printf("Item CleanUp!\n");
	SpriteResource::ClearResourceDir("Items");
	SDL_FreeSurface(smpPickupFrameInfo);
}

void Item::CheckCollision()
{
	if (CPlayState::Instance()->mpPlayer->IsExploding())
		return;
    SDL_Rect playerbox = CPlayState::Instance()->mpPlayer->GetOuterBounds().rect;
    int dx = (playerbox.x + playerbox.w/2) - (mOffset.x - Camera::CameraX()  + mOffset.w/2);
    int dy;
	if (mAir) { dy = (playerbox.y + playerbox.h/2) - (mOffset.y + mOffset.h/2); }
	else { dy = (playerbox.y + playerbox.h/2) - (mOffset.y - Camera::CameraY2() + mOffset.h/2); }
    int radii = playerbox.w/2 + mOffset.w/4;
    if ( ( dx * dx )  + ( dy * dy ) < radii * radii ) 
    {
        pickedup = true;
		if (playerbox.x + playerbox.w/2 < + GAME_BANNER_WIDTH + GAMESCREEN_WIDTH/2) mSpawnSide = 1;
		else mSpawnSide = -1;
    }
}

bool Item::CheckOffscreen(double x, double y, double h)
{
	if( y > GAME_BOUNDS_HEIGHT || x - Camera::CameraX() < 0 || x - Camera::CameraX() > GAME_LEVEL_WIDTH)
		return true;
	else
		return false;
}

void Item::CheckWallCollision(double w, double h)
{
	if (mX < GAME_BANNER_WIDTH) { xvel *= -1; mX = GAME_BANNER_WIDTH; }
	if (mX + w > GAME_LEVEL_WIDTH ) { xvel *= -1; mX = GAME_LEVEL_WIDTH - w; }
	if (mY < 0) { yvel *= -1; mY = 0; }
	if (mY + h > GAME_UI_BOTTOM) { yvel *= -1; mY = GAME_UI_BOTTOM - h; }
}