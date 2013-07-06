#include "Noise.h"
#include "Enemy/Enemy.h"
#include "Engine/SFX.h"

Noise::Noise(bool del, std::string id, bool is_music)
	: Action(del, 0)
{
	mNoiseId = id;
	mMusic = is_music;
}

Noise::~Noise()
{

}

void Noise::Update(Enemy& enemy, Uint32 deltaTicks)
{
	if (enemy.IsHit())
	{
		if (mMusic) SFX::PlaySoundResource(mNoiseId);
		else SFX::PlaySoundResource(mNoiseId);
		mNext =  true;
	}
}