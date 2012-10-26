#include "MType.h"
#include "Engine/SpriteResource.h"
#include "Engine/SFX.h"
#include "State/playstate.h"
#include "Player/Player.h"
#include "Player/Totem.h"
//#include "Beam.h"
#include "BulletM.h"

MType::MType()
{
	printf("MType Crated\n");
	wpn_timer.start();
	level = MAX_TOTEMS;
	SpriteResource::AddResource("Player", "TotemInner.png", 32, 32, 60, 4);
	SpriteResource::AddResource("Player", "Totem.png", 62, 53, 50, 1);
	totem_list[0] = new Totem(40,90, 40,-50);
	totem_list[1] = new Totem(-40,90,-40,-50);
	totem_list[2] = new Totem(80,80, 10,-60);
	totem_list[3] = new Totem(-80,80,-10,-60);
	SpriteResource::AddResource("Player", "Shot.png", 60, 32, 33, 3);
	shotanim = &SpriteResource::RequestResource("Player", "Shot.png");
	rot_divs = 2;
	SpriteResource::AddRotationResource("Player", "MType.png", 12, 38, 300, 1, 0, 360, 12, 38, 6, 19, rot_divs);
	SpriteResource::AddResource("Player", "Conc_Explode.png", 30, 30, 20, 6);
	SpriteResource::AddResource("Player", "Laser.png", 10, 620, 60, 5);
	SpriteResource::AddResource("Player", "Head.png", 36, 37, 20, 4);
	BulletM::Init("MType.png", "Conc_Explode.png");
	minor_speed = 75; major_speed = 75;
	shotanim_clip = 0;
	mov = 0;
	SFX::AddSoundResource("attack.wav");
}

MType::~MType()
{
	printf("MType Deleted\n");
	for (int i=0; i<MAX_TOTEMS; i++)
	{
		delete totem_list[i];
	}
}

void MType::SetPos(int x, int y, int mv)
{
	mov = mv;
	wpn_pos.x = x; wpn_pos.y = y;
}

void MType::MinorAttack(std::list<PlayerBullet*>& pl_bulletlist) 
{		
	if (wpn_timer.get_ticks() > minor_speed  || wpn_timer.is_paused())
	{
		wpn_timer.start(); 	shotanim_clip = 0; shotanim_timer.start();
		SFX::PlaySoundResource("attack.wav");
		
		pl_bulletlist.push_back(new BulletM(wpn_pos.x, wpn_pos.y, 180+mov, rot_divs));
		for (int i=0; i<4; i++)
		{
			int x = totem_list[i]->GetMiddle();
			int y = totem_list[i]->GetVertical();
			for (int i=4; i<10; i+=2)
			{
				pl_bulletlist.push_back(new BulletM(x+(i*2), y+(i*2), 180+(i*2)+mov,rot_divs));
				pl_bulletlist.push_back(new BulletM(x-(i*2), y+(i*2), 180-(i*2)+mov,rot_divs));
			}
		}
	}
}

void MType::MajorAttack(std::list<PlayerBullet*>& pl_bulletlist) 
{ 						
	if (wpn_timer.get_ticks() > major_speed || wpn_timer.is_paused())
	{
		wpn_timer.start(); 	shotanim_clip = 0; shotanim_timer.start();
		SFX::PlaySoundResource("attack.wav");
		
		pl_bulletlist.push_back(new BulletM(wpn_pos.x, wpn_pos.y, 180+mov,rot_divs));
		for (int i=0; i<level; i++)
		{
			int x = totem_list[i]->GetMiddle();
			int y = totem_list[i]->GetVertical();
			for (int i=2; i<10; i+=2)
			{
				pl_bulletlist.push_back(new BulletM(x+(i*2), y+(i*2), 180+(i)+mov,rot_divs));
				pl_bulletlist.push_back(new BulletM(x-(i*2), y+(i*2), 180-(i)+mov,rot_divs));
			}
		}
	}
}

void MType::Shift()
{
	for (int i=0; i<MAX_TOTEMS; i++)
    {
        totem_list[i]->PullTotems();
    }
}

void MType::Unshift()
{
	for (int i=0; i<MAX_TOTEMS; i++)
    {
        totem_list[i]->ReleaseTotems();
    }
}

void MType::StopAttack()
{ 
	if (!wpn_timer.is_paused())
		wpn_timer.pause();
}

void MType::Update(const int& iElapsedTime)
{
	for (int i=0; i<level; i++)
	{
       totem_list[i]->Update(iElapsedTime, wpn_pos.x, wpn_pos.y, !wpn_timer.is_paused());
    }
	Shared::CheckClip(shotanim_timer, shotanim_clip, shotanim->interval, shotanim->clip_count, 0);
}

void MType::Draw(SDL_Surface *dest)
{
	for (int i=0; i<level; i++)
	{
		if (!wpn_timer.is_paused())
			Shared::apply_surface(totem_list[i]->GetMiddle()-shotanim->width/2, totem_list[i]->GetVertical()-shotanim->height/4,
				shotanim->surface,dest, &shotanim->clips[shotanim_clip]);
        totem_list[i]->Draw(dest);
    }
	if (!wpn_timer.is_paused())
		Shared::apply_surface(wpn_pos.x-shotanim->width/2, wpn_pos.y-shotanim->height/2,
			shotanim->surface,dest, &shotanim->clips[shotanim_clip]);
}