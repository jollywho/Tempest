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

	clip = 0; zone_clip = 0; hitbox_clip = 0; booster_clip = 0;

	moveSpeed = SPEED_NORMAL;
    mov = 0;
	left = 0; right = 0; up = 0; down = 0;
	shift = false; attack = false;
    zone_timer.start();
    hitbox_timer.start();
    booster_timer.start();
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
	if (keys.shift) shift = true;
	else shift = false;
	if (keys.z) attack = true;
	else attack = false;
	if (keys.x) bomb = true;
	else bomb = false;
}

void Player::HandleMovement(const int& iElapsedTime)
{
	if (shift && moveSpeed > SPEED_SLOW) moveSpeed-=10;
	if (!shift && moveSpeed < SPEED_NORMAL) moveSpeed+=10;
	//todo: normalize movement
	xVal += ((left + right) * moveSpeed) * (iElapsedTime/1000.f);
	yVal += ((up + down) * moveSpeed) * (iElapsedTime/1000.f);

	if (xVal < _G_BANNER_WIDTH) xVal = _G_BANNER_WIDTH;
	if (xVal + angel->width > _G_BOUNDS_WIDTH) xVal = _G_BOUNDS_WIDTH - angel->width;
	if (yVal < _G_UI_HEIGHT) yVal = _G_UI_HEIGHT;
	if (yVal + angel->height > _G_UI_BOTTOM) yVal = _G_UI_BOTTOM - angel->height;
}

void Player::Update(const int& iElapsedTime)
{
	Shared::CheckClip(clip_timer, clip, angel->interval, angel->clip_count, 0);
	Shared::CheckClip(booster_timer, booster_clip, booster->interval, booster->clip_count, 0);
	Shared::CheckClip(hitbox_timer, hitbox_clip, hitbox->interval, hitbox->clip_count, 0);
	Shared::CheckClip(zone_timer, zone_clip, zone->interval, zone->clip_count, 0);
	HandleMovement(iElapsedTime);
	booster_pos.x = xVal + angel->width/2 - booster->width/2;
	booster_pos.y = yVal + angel->height - booster->height/2;
	hitbox_pos.x = xVal + angel->width/2 - hitbox->width/2;
	hitbox_pos.y = yVal + angel->height - hitbox->height*2;
	zone_pos.x = xVal + angel->width/2 - zone->width/2;
	zone_pos.y = yVal + angel->height/2 - zone->height/2;
}

void Player::Draw(SDL_Surface *dest)
{
    //if (bomb->IsActive())
     //   bomb->show(dest);

	//move to separate function for draw order
	if (shift)
		Shared::apply_surface(zone_pos.x, zone_pos.y, zone->surface, dest, &zone->clips[zone_clip]);
	Shared::apply_surface(booster_pos.x, booster_pos.y, booster->surface, dest, &booster->clips[booster_clip]);
	Shared::apply_surface(xVal, yVal, angel->surface, dest, &angel->clips[clip]);
	Shared::apply_surface(hitbox_pos.x, hitbox_pos.y, hitbox->surface, dest, &hitbox->clips[hitbox_clip]);
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