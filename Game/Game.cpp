#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Item.h"
#include "GameOver.h"
#include "GameClear.h"


Game::Game()
{
	m_player = FindGO<Player>("battleCharacter");
}



Game::~Game()
{

	DeleteGO(m_player);

	DeleteGO(m_backGround);

	DeleteGO(m_gameCamera);

	auto totalItem = FindGOs<Item>("item");
	for (auto Items : totalItem) {
		DeleteGO(Items);
	}

}

bool Game::Start()
{
	//プレイヤーのオブジェクトを読み込む
	m_player = NewGO<Player>(0, "battleCharacter");

	//背景を読み込む
	m_backGround = NewGO<BackGround>(0, "backGround");

	//ゲームカメラを読み込む
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");

	//アイテムを読み込む
	MakeItems({ 0.0f, 25.0f, 1100.0f });
	MakeItems({ 0.0f, 420.0f, 2460.0f });
	MakeItems({ 0.0f, 740.0f, 3950.0f });
	MakeItems({ 0.0f, -870.0f, 4100.0f });
	MakeItems({ 0.0f, -380.0f, 6500.0f });

	m_gameState = enGameState_Play;
	gameClear = false;
	gameOver = false;
	SkyCube* sky = NewGO<SkyCube>(0);//SkyCubeから飛んで
	sky->SetLuminance(0.2f);//明るさ調節
	sky->SetType(enSkyCubeType_NightToon_2);//ここの()の中に空の風景を入れる
	return true;
}

void Game::MakeItems(const Vector3& itemPos)
{
	m_item = NewGO<Item>(0, "item");
	m_item->m_position = itemPos;
	m_item->m_firstPosition = itemPos;
}

void Game::Update()
{
	ManageGameState();

	if (gameOver == true) {
		NewGO<GameOver>(0, "gameOver");
		DeleteGO(this);
	}

	if (gameClear == true) {
		NewGO<GameClear>(0, "gameClear");
		DeleteGO(this);
	}
}

void Game::ManageGameState()
{
	if (m_player->m_position.y <= -1000.0f) {
		m_gameState = enGameState_GameOver;
		gameOver = true;
	}

	if (m_item->m_itemCount == m_item->m_maxItemCount) {
		m_gameState = enGameState_GameClear;
		gameClear = true;
	}

	
}

