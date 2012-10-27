#include "ScoreMSG.h"
#include "Game/Camera.h"
#include "State/playstate.h"
#include "Game/Interface.h"
#include "Player/Player.h"
#include "Game/Gamescore.h"

SDL_Surface* ScoreMSG::surfaceFade[4];
NFont ScoreMSG::fontFade[4];
Timer ScoreMSG::tallyTimer;
int ScoreMSG::tallyTotal = 0;
int ScoreMSG::extend = 0;

ScoreMSG::ScoreMSG(int x, int y, int xDir, int value)
{
	clip = 0;

	if (tallyTimer.get_ticks() < 50 && extend < 2000)
	{
		m_delete = true;
		tallyTotal += value;
		extend += 50;
		GameScore::Instance()->IncreaseScore(value);
	}
	else
	{
		extend = 0;
		tallyTotal = value;
		m_delete = false;
		val = value;
		msg << "+" << val;
		GameScore::Instance()->IncreaseScore(value);
		xVal = x + (rand() % 20)-40; 
		yVal = y - (rand() % 20)+40;

		xVel = (xDir * 50);
		yVel = -50;
		duration_Timer.start();
		clip_Timer.start();
	}
	tallyTimer.start();
}

ScoreMSG::~ScoreMSG()
{
}

void ScoreMSG::Init()
{
	for (int i=0; i<4; i++)
	{
		std::stringstream ss;
		ss << "Font/GoldNoonFade"<< i << ".png";
		surfaceFade[i] = Shared::load_image(ss.str());
		fontFade[i].load(SDL_GetVideoSurface(), surfaceFade[i]);
	}
	tallyTimer.start();
}

void ScoreMSG::CleanUp()
{
	for (int i=0; i<4; i++)
		SDL_FreeSurface(surfaceFade[i]);
}

void ScoreMSG::Update(Uint32 deltaTicks)
{
	Shared::CheckClip(clip_Timer, clip, 300 + extend, 3, 3);
	xVal += xVel * (deltaTicks/1000.f);
	yVal += yVel * (deltaTicks/1000.f);
	if (duration_Timer.get_ticks() > 800 + extend) { m_delete = true; }
	if (val < tallyTotal)
		val++;
	msg.str("");
	msg << "+" << val;
}

void ScoreMSG::Draw(SDL_Surface *dest)
{
	fontFade[clip].draw(xVal-Camera::CameraX(),yVal,msg.str().c_str());
}