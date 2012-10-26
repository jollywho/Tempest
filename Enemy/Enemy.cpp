#include "Enemy.h"
#include "Game/Camera.h"
#include "Engine/SpriteResource.h"
#include "Player/Player.h"
#include "State/Playstate.h"

SDL_Surface* Enemy::explo_surface;
SDL_Surface* Enemy::hit_surface;
SDL_Color Enemy::hitColor = { 255, 0, 0 };

Enemy::Enemy(float x, float y, int hp, std::string id)
{
	printf("Enemy Created\n");

	info = &SpriteResource::RequestResource("Enemy", id);

	active = false;
    m_delete = false;
    exploding = false;
    hit = false;
	clip = 0;
	xVal = x - info->width/2; 
	yVal = y - info->height/2;
	hitbox.x = xVal; hitbox.y = yVal;
	hitbox.w = info->width; hitbox.h = info->height;
	health = hp;
}

void Enemy::Init()
{
    explo_surface = Shared::load_image("Image/Enemies/En_Explo.png");
    hit_surface = Shared::load_image("Image/Enemies/HitColor.png");
}

void Enemy::CleanUp()
{
    SDL_FreeSurface(explo_surface);
    SDL_FreeSurface(hit_surface);
}

void Enemy::FlashRed(SDL_Surface* en_surface, SDL_Rect* targetClip)
{
	if (!hit_timer.is_started()) hit_timer.start();
    if (!hit && hit_timer.get_ticks() > 45)
    {
		hit = true;
		hit_timer.start();
		copy_surface = SDL_ConvertSurface(en_surface, en_surface->format, SDL_SWSURFACE);
		Shared::apply_surface(targetClip->x, targetClip->y, hit_surface, copy_surface, NULL);
    }
}

void Enemy::FlashClear()
{
	if (hit && hit_timer.get_ticks() > 45)
	{
		hit = false;
		hit_timer.start();
		SDL_FreeSurface(copy_surface);
	}
}


bool Enemy::CheckBounds(float x, float y, float h)
{
	if( y - Camera::CameraY() > 0 && yVal + h >= Camera::CameraY())
		return false;
	else
		return true;
}

bool Enemy::Explode(bool del)
{
	return false;

	//todo: connect with explosion manager.
}

bool Enemy::MonitorHealth()
{
	if (health <= 0)
		exploding = true;
	//todo: request explosion
	return false;
}

void Enemy::DetectCollisions()
{
	SDL_Rect pl = CPlayState::Instance()->player->GetBounds();

	if (hitbox.x+hitbox.w>pl.x  && 
        hitbox.x<pl.x+pl.w  && 
        hitbox.y+hitbox.h>pl.y && 
        hitbox.y<pl.y+pl.h)
        { 
            TakeHit(1);
			CPlayState::Instance()->player->TakeHit();
		}
}