#pragma once
#include "sound/SoundSource.h"

class Player;

class Item :public IGameObject
{
public:
	Item();
	~Item();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();

	ModelRender m_modelRender;	//モデルレンダー
	Vector3 m_position;			//座標
	Vector3 m_firstPosition;	//初期座標
	Quaternion m_rotation;		//回転
	Player* m_player;			//プレイヤー
	SoundSource* m_getSE;		//BGM
	int m_itemCount = 0;		//アイテム取得数
	int m_maxItemCount = 5;		//最大アイテム数

	enum EnMoveState {
		enMoveState_Up,
		enMoveState_Down,
		enMoveState_Num
	};
	int m_moveState = 0;
};

