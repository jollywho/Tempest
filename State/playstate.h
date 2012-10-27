#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "State/Gamestate.h"
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

	void CheckKeys(const KeyStruct& keys);
	void Update(const int& iElapsedTime);
	void Draw(SDL_Surface* dest);

    void ClearObjects();

	static CPlayState* Instance() {
		return &m_PlayState;
	}

    void NewLevel();
    int stage;
	bool m_Exit;
	bool m_Enter;

    std::list<EnemyBullet*> en_bulletlist;
	std::list<PlayerBullet*> pl_bulletlist;
	std::list<Enemy*> enemy_list;
	std::list<Item*> item_list;
	std::list<ScoreMSG*> score_list;
	//explosionlist
	Player* player;
	Level* level;
	Interface* ui;
protected:
	CPlayState() { }
    ~CPlayState();

	template <class T>
	void UpdateList(std::list<T>& lst, const int& iElapsedTime);

	template <class T>
	void DrawList(std::list<T>& lst, SDL_Surface* dest);
private:
	static CPlayState m_PlayState;
	Timer scan_timer;
	int alpha;
	Timer fade_timer;
};

#endif
