#include "Enemy.h"
#include "Game/Camera.h"
#include "Engine/SpriteResource.h"
#include "Player/Player.h"
#include "State/Playstate.h"

SDL_Surface* Enemy::hit_surface;
SDL_Color Enemy::hitColor = { 255, 0, 0 };

Enemy::Enemy(int x, int y, int hp, std::string id)
{
	printf("Enemy Created\n");

	info = &SpriteResource::RequestResource("Enemies", id);
	clip_timer.start();

    m_delete = false;
    exploding = false;
    hit = false;
	clip = 0;
	xVal = x - info->width/2; 
	yVal = y - info->height/2;
	hitbox.x = xVal; 
	hitbox.y = yVal;
	hitbox.w = info->width; hitbox.h = info->height;
	health = hp;
}

void Enemy::Init()
{
    hit_surface = Shared::load_image("Image/Enemies/HitColor.png");
}

void Enemy::CleanUp()
{
    SDL_FreeSurface(hit_surface);
}

void Enemy::FlashRed(SDL_Surface* en_surface, SDL_Rect* targetClip)
{
    if (!hit)
    {
		hit = true;
		hit_timer.start();
		copy_surface = SDL_ConvertSurface(en_surface, en_surface->format, SDL_SWSURFACE);
		Shared::apply_surface(targetClip->x, targetClip->y, hit_surface, copy_surface, NULL);
    }
}

void Enemy::FlashClear()
{
	if (hit && hit_timer.get_ticks() > 30)
	{
		hit = false;
		SDL_FreeSurface(copy_surface);
	}
}

bool Enemy::CheckBounds()
{
	if( yVal + info->height - Camera::CameraY2() > 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Enemy::Explode(bool del)
{
	if (exploding)
	{
		m_delete = del;
		return true;
	}
	else
		return false;

	//todo: connect with explosion manager.
}

bool Enemy::CheckHealth()
{
	FlashClear();
	if (health <= 0)
		exploding = true;
	//todo: request explosion
	return false;
}

void Enemy::DetectCollision()
{
	if( yVal - Camera::CameraY2() > _G_BOUNDS_HEIGHT)
	{
		m_delete = true;
		return;
	}

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