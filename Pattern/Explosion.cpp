#include "Explosion.h"
#include "Game/Camera.h"
#include "State/Playstate.h"
#include "Engine/SpriteResource.h"
#include "Level/Level.h"

std::map<std::string, std::list<ExplosionInfo>> Explosion::explosions;

Explosion::Explosion(int x, int y, int xv, int yv, ExplosionInfo nfo)
{
	m_delete = false;
	info = &SpriteResource::RequestResource("Explosion", nfo.spriteId);
	xVal = x-info->width/2 + nfo.offsetX;
	yVal = y-info->height/2 + nfo.offsetY;
	xVel = xv; yVel = yv;
	clip = 0;
	detTime = nfo.delay;

	if (nfo.magnitude > 4)
		Camera::Instance()->StartShake(nfo.magnitude);

	//if (nfo.residue)
	//	CPlayState::Instance()->mpLevel->objectList.push_back(new LayerObjbect(x, y));

	if (detTime != 0)  started = false;
	else started = true;

	clip_Timer.Start();
}

void Explosion::AddExplosionInfo(std::string expId, std::string spriteId,
	int magnitude, int delay, int offsetX, int offsetY, bool residue)
{
	std::list<ExplosionInfo> dataList;
	ExplosionInfo data;
	data.spriteId = spriteId; data.delay = delay; data.residue = residue;
	data.offsetX = offsetX; data.offsetY = offsetY; data.magnitude = magnitude;
	auto temp = explosions.find(expId);
	if (temp == explosions.end()) {
		dataList.push_back(data);
		explosions.insert(std::make_pair(expId,  dataList));
	}
	else
		temp->second.push_back(data);
}

void Explosion::RequestExplosion(std::string expId, int x, int y, int xv, int yv)
{
	printf("%s requested: \n", expId.c_str());
	auto temp = explosions.find(expId)->second;
	std::list<ExplosionInfo>::const_iterator it;
	for (auto it = temp.begin(); it != temp.end(); it++)
	{
		printf("Explosion %s\n", it->spriteId.c_str());
		CPlayState::Instance()->explosion_list.push_back(new Explosion(x,y,xv,yv,*it));
	}
}

void Explosion::ClearList()
{
	explosions.clear();
}

void Explosion::Update(Uint32 deltaTicks)
{
	if (!started && clip_Timer.GetTicks() > detTime) {
		started = true; clip_Timer.Start(); }
	if (started)
	{
		if (clip >= info->maxClips-1)
			m_delete = true;
		Shared::CheckClip(clip_Timer, clip, info->interval, info->maxClips, 0);
		xVal += xVel * ( deltaTicks / 1000.f );
		yVal += yVel * ( deltaTicks / 1000.f );
	}
}

void Explosion::Draw(SDL_Surface *dest)
{
	if (started)
		Camera::Instance()->DrawSurface(xVal, yVal, info->pSurface, dest, &info->pClips[clip]);
}