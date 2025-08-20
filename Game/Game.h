#pragma once
#include "Level3DRender/LevelRender.h"
class Player;
class BackGround;
class GameCamera;
class Item;
class GameOver;
class GameClear;

class Game : public IGameObject
{
public:
	Game();
	~Game();	
	bool Start();
	void Update();
	void MakeItems(const Vector3& itemPos);
	void ManageGameState();

	enum EnGameState {
		enGameStete_Title,
		enGameState_Play,
		enGameState_GameClear,
		enGameState_GameOver,
		enGameState_Num
	};


	//Ç±Ç±Ç©ÇÁÉÅÉìÉoïœêî
	int m_gameState = 0;
	bool gameOver = false;
	bool gameClear = false;
	Player* m_player = nullptr;
	BackGround* m_backGround = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameOver* m_gameOver = nullptr;
	GameClear* m_gameClear = nullptr;
	Item* m_item = nullptr;
	
};

