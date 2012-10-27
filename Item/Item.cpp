#include "Item.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"
#include "Game/Interface.h"
#include "Game/Camera.h"
#include "Player/Player.h"

SDL_Surface* Item::received_frame;

Item::Item(int x, int y, int value, char* id)
{
	_info = &SpriteResource::RequestResource("Items", id);
    m_delete = false; pickedup = false; received = false;
    val = 25; clip = 0;
	xVal = x - _info->width/2;
    yVal = y - _info->height/2 - Camera::CameraY2();
    offset.x = xVal;
    offset.y = yVal;
    offset.w = _info->width;
    offset.h = _info->height;
	clip_Timer.start();
	duration_Timer.start();
}

Item::~Item() {}

void Item::SetBonus(int val)
{
	
}

void Item::Init()
{
	printf("Item Init!\n");
	SpriteResource::AddResource("Items", "Gem.png", 32, 32, 60, 8);
	SpriteResource::AddResource("Items", "Coin.png", 32, 32, 60, 6);
	SpriteResource::AddResource("Items", "bombup.png", 48, 48, 60, 5);
	SpriteResource::AddResource("Items", "Powerup.png", 64, 64, 60, 4);
	SpriteResource::AddResource("Items", "Chest.png", 34, 40, 160, 4);
	SpriteResource::AddResource("Items", "Quartz.png", 32, 44, 30, 7);

	SpriteResource::AddResource("Items", "Bomb_Received.png", 70, 15, 60, 5, true);
	SpriteResource::AddResource("Items", "Powerup_Received.png", 86, 15, 60, 6, true);
	received_frame = Shared::load_image("Image/Items/Receive_Frame.png");

	SFX::AddSoundResource("damage.wav");
	SFX::AddSoundResource("pickup.wav");
	SFX::AddSoundResource("powerup_pickup.wav");
	SFX::AddSoundResource("bomb_pickup.wav");
	SFX::AddSoundResource("gem_pickup.wav");
	SFX::AddSoundResource("coin_pickup.wav");
	SFX::AddSoundResource("tick.wav");
}

void Item::CleanUp()
{
	printf("Item CleanUp!\n");
	SpriteResource::ClearResourceDir("Items");
	SDL_FreeSurface(received_frame);
}

void Item::Check_Collision()
{
	if (CPlayState::Instance()->player->IsExploding())
		return;
    SDL_Rect playerbox = CPlayState::Instance()->player->GetOuterBounds();
    int dx = (playerbox.x + playerbox.w/2) - (offset.x - Camera::CameraX()  + offset.w/2);
    int dy;
	if (Air) { dy = (playerbox.y + playerbox.h/2) - (offset.y + offset.h/2); }
	else { dy = (playerbox.y + playerbox.h/2) - (offset.y - Camera::CameraY2() + offset.h/2); }
    int radii = playerbox.w/2 + offset.w/4;
    if ( ( dx * dx )  + ( dy * dy ) < radii * radii ) 
    {
        pickedup = true;
		if (playerbox.x + playerbox.w/2 < + _G_BANNER_WIDTH + _GSCREEN_WIDTH/2) spawnside = 1;
		else spawnside = -1;
    }
}

bool Item::CheckOffscreen(double x, double y, double h)
{
	if( y > _G_BOUNDS_HEIGHT || x - Camera::CameraX() < 0 || x - Camera::CameraX() > _G_LEVEL_WIDTH)
		return true;
	else
		return false;
}

void Item::Check_WallCollision(double w, double h)
{
	if (xVal < _G_BANNER_WIDTH) { xVel *= -1; xVal = _G_BANNER_WIDTH; }
	if (xVal + w > _G_LEVEL_WIDTH ) { xVel *= -1; xVal = _G_LEVEL_WIDTH - w; }
	if (yVal < 0) { yVel *= -1; yVal = 0; }
	if (yVal + h > _G_UI_BOTTOM) { yVel *= -1; yVal = _G_UI_BOTTOM - h; }
}