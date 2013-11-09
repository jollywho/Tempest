/* Tempest - C++ Danmakufu Game for SDL
*
*  Copyright (C) 2013 Kevin Vollmer.
*  
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*  
ÅÅ*  Kevin Vollmer <works.kvollmer@gmail.com>
*
*/
#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "gamestate.h"
#include <list>
#include "Player/Player.h"

class Level;
class Interface;
class Enemy;
class PlayerBullet;
class EnemyBullet;
class Item;
class ScoreMSG;
class Explosion;

class CPlayState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void KeyInput(const SDL_Event& rEvent);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* dest);

    void ClearObjects();

	void NewLevel();

	static CPlayState* Instance() {
		return &mPlayState;
	}

	bool mExit;
	bool mEnter;
	bool mReturn;

    std::list<EnemyBullet*> en_bulletlist;
	std::list<PlayerBullet*> pl_bulletlist;
	std::list<Enemy*> enemy_list;
	std::list<Item*> item_list;
	std::list<ScoreMSG*> score_list;
	std::list<Explosion*> explosion_list;
	//explosionlist
	Player* mpPlayer;
	Level* mpLevel;
	Interface* mpInterface;
protected:
	CPlayState() { }
    ~CPlayState();

	template <class T>
	void UpdateList(std::list<T>& rList, const int& rDeltaTime);

	template <class T>
	void DrawList(std::list<T>& rList, SDL_Surface* dest);
private:
	static CPlayState mPlayState;
	Timer mScanTimer;
	int mAlpha;
	Timer mFadeTimer;
};

#endif
