#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "Gamestate.h"
#include <list>
#include "Player/Player.h"

class Level;

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
    static bool m_Exit;

    //std::list<EnemyBullet*> en_bulletlist;
	//std::list<PlayerBullet*> pl_bulletlist
	//std::list<Enemy*> enemy_list;
	//std::list<Item*> item_list;
	//explosionlist
	Player* player;
	Level* level;
protected:
	CPlayState() { }
    ~CPlayState();
private:
	static CPlayState m_PlayState;
};

#endif
