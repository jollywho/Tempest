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

class CPlayState : public CGameState
{
public:
	void Init();
	void Cleanup();

	void Pause();
	void Resume();

	void KeyInput(const KeyStruct& rKeys);
	void Update(const int& rDeltaTime);
	void Draw(SDL_Surface* dest);

    void ClearObjects();

	void NewLevel();

	static CPlayState* Instance() {
		return &mPlayState;
	}

	bool mExit;
	bool mEnter;

    std::list<EnemyBullet*> en_bulletlist;
	std::list<PlayerBullet*> pl_bulletlist;
	std::list<Enemy*> enemy_list;
	std::list<Item*> item_list;
	std::list<ScoreMSG*> score_list;
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
