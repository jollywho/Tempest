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
	wpn_timer.Start();
	level = MAX_TOTEMS;
	mpTotemList[0] = new Totem(40,90, 40,-50);
	mpTotemList[1] = new Totem(-40,90,-40,-50);
	mpTotemList[2] = new Totem(80,80, 10,-60);
	mpTotemList[3] = new Totem(-80,80,-10,-60);
	mpShotAnim = &SpriteResource::RequestResource("Player", "Shot.png");
	rot_divs = 2;
	SpriteResource::AddRotationResource("Player", "MType.png", 12, 38, 300, 1, 0, 360, 12, 38, 6, 19, rot_divs);
	BulletM::Init("MType.png", "Conc_Explode.png");
	minor_speed = 90; major_speed = 90;
	mShotAnimClip = 0;
	mov = 0;
	SFX::AddSoundResource("attack.wav");
	SFX::AddSoundResource("bomb.wav");
	SFX::AddSoundResource("bomb2.wav");
}

MType::~MType()
{
	printf("MType Deleted\n");
	for (int i=0; i<MAX_TOTEMS; i++)
	{
		delete mpTotemList[i];
	}
}

void MType::SetPos(int x, int y, int mv)
{
	mov = mv;
	wpn_pos.x = x; wpn_pos.y = y;
}

void MType::ResetPos(int x, int y) 
{
	wpn_pos.x = x; wpn_pos.y = y;
	for (int i=0; i<MAX_TOTEMS; i++)
		mpTotemList[i]->ResetPos(x, y);
}

void MType::MinorAttack(std::list<PlayerBullet*>& pl_bulletlist) 
{		
	if (wpn_timer.GetTicks() > minor_speed  || wpn_timer.IsPaused())
	{
		wpn_timer.Start(); 	mShotAnimClip = 0; mShotAnimTimer.Start();
		SFX::PlaySoundResource("attack.wav");
		
		pl_bulletlist.push_back(new BulletM(wpn_pos.x, wpn_pos.y, 180+mov, rot_divs));
		for (int i=0; i<4; i++)
		{
			int x = mpTotemList[i]->GetMiddle();
			int y = mpTotemList[i]->GetVertical();
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
	if (wpn_timer.GetTicks() > major_speed || wpn_timer.IsPaused())
	{
		wpn_timer.Start(); 	mShotAnimClip = 0; mShotAnimTimer.Start();
		SFX::PlaySoundResource("attack.wav");
		
		pl_bulletlist.push_back(new BulletM(wpn_pos.x, wpn_pos.y, 180+mov,rot_divs));
		for (int i=0; i<level; i++)
		{
			int x = mpTotemList[i]->GetMiddle();
			int y = mpTotemList[i]->GetVertical();
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
        mpTotemList[i]->PullTotems();
    }
}

void MType::Unshift()
{
	for (int i=0; i<MAX_TOTEMS; i++)
    {
        mpTotemList[i]->ReleaseTotems();
    }
}

void MType::StopAttack()
{ 
	if (!wpn_timer.IsPaused())
		wpn_timer.Pause();
}

void MType::Update(const int& rDeltaTime)
{
	for (int i=0; i<level; i++)
	{
       mpTotemList[i]->Update(rDeltaTime, wpn_pos.x, wpn_pos.y, !wpn_timer.IsPaused());
    }
	Shared::CheckClip(mShotAnimTimer, mShotAnimClip, mpShotAnim->interval, mpShotAnim->maxClips, 0);
}

void MType::Draw(SDL_Surface *pDest)
{
	for (int i=0; i<level; i++)
	{
		if (!wpn_timer.IsPaused())
			Shared::DrawSurface(mpTotemList[i]->GetMiddle() - mpShotAnim->width/2, mpTotemList[i]->GetVertical()- mpShotAnim->height/4,
				mpShotAnim->pSurface, pDest, &mpShotAnim->pClips[mShotAnimClip]);
        mpTotemList[i]->Draw(pDest);
    }
	if (!wpn_timer.IsPaused())
		Shared::DrawSurface(wpn_pos.x - mpShotAnim->width/2, wpn_pos.y - mpShotAnim->height/2,
			mpShotAnim->pSurface, pDest, &mpShotAnim->pClips[mShotAnimClip]);
}