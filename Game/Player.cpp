#include "stdafx.h"
#include "Player.h"
#include "GameOver.h"
Player::Player()
{
	//アニメーションをロードする
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);

	//モデルを初期化する
	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);

	m_characterController.Init(25.0f, 75.0f, m_position);
}

Player::~Player()
{
	
}

void Player::Update()
{
	//移動処理
	Move();
	//回転処理
	Rotation();
	//ステート処理
	ManagePlayerState();
	
	//アニメーションの再生
	PlayAnimation();

	m_modelRender.Update();
}

void Player::Move()
{
	//xzの移動速度を0.0fにする
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_dashSpeed.x = m_moveSpeed.x * 2;
	m_dashSpeed.z = m_moveSpeed.z * 2;
	//左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//Y方向には移動しない
	forward.y = 0.0f;
	right.y = 0.0f;

	//左スティックの入力量と120.0fを乗算
	right *= stickL.x * 240.0f;
	forward *= stickL.y * 240.0f;

	//移動速度に上記で計算したベクトルを持ってくる
	m_moveSpeed += right + forward;

	if (g_pad[0]->IsPress(enButtonB))
	{
		m_moveSpeed.x *= 2.0f;
		m_moveSpeed.z *= 2.0f;
	}

	
	ManageJumpState();
	

	////リスポーン
	//if (m_position.y <= -100.0f)
	//{
	//	m_position = m_RePosition;
	//	m_moveSpeed = Vector3::Zero;
	//	m_characterController.SetPosition(m_position);
	//}

	
	


	//キャラコンで移動
	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	m_modelRender.SetPosition(m_position);
}

//回転処理
void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);

		m_modelRender.SetRotation(m_rotation);
	}
}

//プレイヤーのステート処理
void Player::ManagePlayerState()		//ステート処理
{
	if (m_characterController.IsOnGround() == false) {
		m_playerState = enState_Jump;
		return;
		//もし地面についていなかったらプレイヤーのステートをenState_Jumpにする
	}

	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f){
		m_playerState = enState_Walk;
		//もしスティックの入力があったらプレイヤーのステートをenState_Walkにする
		
		if (g_pad[0]->IsPress(enButtonB)) {
			m_playerState = enState_Run;
		}
		//もし移動中にBボタンが押されたらプレイヤーのステートをenState_Runにする
	}

	else {
		m_playerState = enState_Idle;
		//もし何もしていなかったらプレイヤーのステートをenState_Idleにする
	}
}

void Player::ManageJumpState()
{
	
	//地面についていたら
	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;//重力をなくす
		m_jumpCount = 0;
	}
	//地面についていなかったら
	else {
		m_moveSpeed.y -= m_gravity;
	}

	if (m_jumpCount < m_maxJumpCount)
	{
		m_jump = true;
	}
	else if (m_jumpCount >= m_maxJumpCount)
	{
		m_jump = false;
	}

	if (m_jump)
	{
		//ジャンプさせる
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_moveSpeed.y += 600.0f;
			m_jumpCount++;
		}
	}
	
}

void Player::PlayAnimation()
{
	switch (m_playerState)
	{
	case enState_Idle:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case enState_Jump:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	case enState_Walk:
		m_modelRender.PlayAnimation(enAnimationClip_Walk); 
		break;
	case enState_Run:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}

void Player::Render(RenderContext& renderContext)
{
	//モデルを表示する
	m_modelRender.Draw(renderContext);
}