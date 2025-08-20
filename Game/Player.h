#pragma once
class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update();					//更新処理
	void Render(RenderContext& renderContext);		//描画処理
	void Move();		//移動処理
	void Rotation();	//回転処理
	void ManagePlayerState();	//ステート管理
	void ManageJumpState();		//新しく作る関数（ジャンプステート関数）
	void PlayAnimation();
	

	enum EnAnimation {
		enAnimationClip_Idle,
		enAnimationClip_Jump,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Num
	};

	enum EnPlayerState {
		enState_Idle,
		enState_Jump,
		enState_Walk,
		enState_Run,
		enState_Num
	};

	//ここからメンバ変数
	ModelRender m_modelRender;
	CharacterController m_characterController;
	Quaternion m_rotation; //クオータニオン
	Vector3 m_moveSpeed;
	Vector3 m_dashSpeed;
	Vector3 m_position;		//座標
	float m_gravity = 9.8 * 2.5f;
	bool m_jump = true;
	int m_jumpCount = 0;	
	int m_maxJumpCount = 2;	
	int m_playerState = 0;
	AnimationClip m_animationClips[enAnimationClip_Num];

};

