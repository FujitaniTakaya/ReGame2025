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

	ModelRender m_modelRender;	//���f�������_�[
	Vector3 m_position;			//���W
	Vector3 m_firstPosition;	//�������W
	Quaternion m_rotation;		//��]
	Player* m_player;			//�v���C���[
	SoundSource* m_getSE;		//BGM
	int m_itemCount = 0;		//�A�C�e���擾��
	int m_maxItemCount = 5;		//�ő�A�C�e����

	enum EnMoveState {
		enMoveState_Up,
		enMoveState_Down,
		enMoveState_Num
	};
	int m_moveState = 0;
};

