#include "Player.h"
#include "Engine/SpriteResource.h"
#include "State/playstate.h"

void Player::ReSpawn()
{

}

Player::Player() 
{
	printf("Player Created\n");
	SpriteResource::AddResource("Player", "angel.png", 64, 64, 120, 4);
	SpriteResource::AddResource("Player", "hitbox.png", 20, 20, 60, 8);
	SpriteResource::AddResource("Player", "booster.png", 38, 38, 60, 5);
	SpriteResource::AddResource("Player", "zone.png", 120, 120, 60, 4);

	angel = &SpriteResource::RequestResource("Player", "angel.png");
	hitbox = &SpriteResource::RequestResource("Player", "hitbox.png");
	booster = &SpriteResource::RequestResource("Player", "booster.png");
	zone = &SpriteResource::RequestResource("Player", "zone.png");

	clip = 0; zone_clip = 0; hitbox_clip = 0; boost_clip = 0;

	moveSpeed = SPEED_NORMAL;
    mov = 0;
	left = 0; right = 0; up = 0; down = 0;
	shift = false; attack = false;
    zone_timer.start();
    hitbox_timer.start();
    boost_timer.start();
	clip_timer.start();

    xVal = _G_LEVEL_WIDTH/2 + 192/2;
    yVal = _G_BOUNDS_HEIGHT/2 + 192/4;
}

Player::~Player()
{
	printf("Player Deleted\n");
	SpriteResource::ClearResourceDir("Player");
}

void Player::CheckKeys(const KeyStruct& keys)
{
	if (keys.up) up = -1;
	else up = 0;
	if (keys.down) down = 1;
	else down = 0;
	if (keys.left) left = -1;
	else left = 0;
	if (keys.right) right = 1;
	else right = 0;
}

void Player::HandleMovement(const int& iElapsedTime)
{
	//todo: normalize movement
	//todo: slow movement over time from shift/unshift
	xVal += ((left + right) * 600) * (iElapsedTime/1000.f);
	yVal += ((up + down) * 600) * (iElapsedTime/1000.f);

	if (xVal < _G_BANNER_WIDTH) xVal = _G_BANNER_WIDTH;
	if (xVal + angel->width > _G_BOUNDS_WIDTH) xVal = _G_BOUNDS_WIDTH - angel->width;
	if (yVal < _G_UI_HEIGHT) yVal = _G_UI_HEIGHT;
	if (yVal + angel->height > _G_UI_BOTTOM) yVal = _G_UI_BOTTOM - angel->height;
}

void Player::Update(const int& iElapsedTime)
{
	Shared::CheckClip(clip_timer, clip, angel->interval, angel->clip_count, 0);
	HandleMovement(iElapsedTime);
}

void Player::Draw(SDL_Surface *dest)
{
    //if (bomb->IsActive())
     //   bomb->show(dest);

	//move to separate function for draw order
	//if (shift)
	Shared::apply_surface(xVal, yVal, angel->surface, dest, &angel->clips[clip]);
}

SDL_Rect Player::GetBounds()
{
	SDL_Rect temp = {hitbox_pos.x, hitbox_pos.y, hitbox->width, hitbox->height};
    return temp;
}

SDL_Rect Player::GetOuterBounds()
{
	SDL_Rect temp = {xVal, yVal, angel->width, angel->height};
    return temp;
}

void Player::TakeHit()
{
	//die
}