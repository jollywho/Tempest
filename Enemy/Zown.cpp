#include "Zown.h"
#include "State/playstate.h"
#include "Engine/SpriteResource.h"
#include "Game/Camera.h"

Zown::Zown(int x, int y) : Enemy(x, y, 150, "zown.png")
{
	air = false;
	bullet_wipe = true;

    rot = 0; attackCount = 0;
	attack_Timer.start();
}

Zown::~Zown()
{
    if (hit)
        SDL_FreeSurface(copy_surface);

}

void Zown::TakeHit(int dmg)
{
    health -= dmg;
    FlashRed(info->surface, &info->clips[clip]);
}

void Zown::Init()
{
	printf("Zown Init\n");
	SpriteResource::AddResource("Enemies", "zown.png", 64, 64, 60, 3);
	//todo: relink
	//Explosion::AddExplosionInfo("Zown", "Exp_ThinImplode.png", 5, 0);
}

void Zown::CleanUp()
{

}

void Zown::Attack()
{
	/*
	attackCount++;
	
	if (attackCount > 3) attackCount = 1;

	rot += .4;
	if (rot > M_PI)
		rot = 0;
	
	for (double i=0-rot; i<=M_PI/2+rot - .4; i+= .4 )
    {
        double x = cos(i);
        double y = sin(i);
        CPlayState::Instance()->en_bulletlist.push_back(new VectorBullet(atkgateLEFT_offset.x + GATE_WIDTH/2,
			atkgateLEFT_offset.y + GATE_WIDTH/2,
			x*100, y * 100, "LargeRed.png"));

		CPlayState::Instance()->en_bulletlist.push_back(new VectorBullet(atkgateRIGHT_offset.x + GATE_WIDTH/2,
			atkgateRIGHT_offset.y + GATE_WIDTH/2,
			-x*100, y * 100, "LargeRed.png"));
    }
    attack_Timer.start();
	*/
}

void Zown::Update(Uint32 deltaTicks)
{
	if (Explode(true)) return;
	if (CheckHealth()) return;
	DetectCollisions();

    if (attack_Timer.get_ticks() > 80)
        Attack();
	Shared::CheckClip(clip_timer, clip, info->interval, info->clip_count, 0);
	
    hitbox.x = xVal ;
    hitbox.y = yVal ;
}

void Zown::Draw(SDL_Surface *dest)
{
	if (exploding) return;

    if (hit)
        Camera::DrawSurface(hitbox.x, hitbox.y,
            copy_surface, dest, &info->clips[clip]);
    else
        Camera::DrawSurface(hitbox.x, hitbox.y,
            info->surface, dest, &info->clips[clip]);
}