#include "stdafx.h"
#include "Player.h"
#include "GameOver.h"
Player::Player()
{
	//�A�j���[�V���������[�h����
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);

	//���f��������������
	m_modelRender.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);

	m_characterController.Init(25.0f, 75.0f, m_position);
}

Player::~Player()
{
	
}

void Player::Update()
{
	//�ړ�����
	Move();
	//��]����
	Rotation();
	//�X�e�[�g����
	ManagePlayerState();
	
	//�A�j���[�V�����̍Đ�
	PlayAnimation();

	m_modelRender.Update();
}

void Player::Move()
{
	//xz�̈ړ����x��0.0f�ɂ���
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_dashSpeed.x = m_moveSpeed.x * 2;
	m_dashSpeed.z = m_moveSpeed.z * 2;
	//���X�e�B�b�N�̓��͗ʂ��擾
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//Y�����ɂ͈ړ����Ȃ�
	forward.y = 0.0f;
	right.y = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ�120.0f����Z
	right *= stickL.x * 240.0f;
	forward *= stickL.y * 240.0f;

	//�ړ����x�ɏ�L�Ōv�Z�����x�N�g���������Ă���
	m_moveSpeed += right + forward;

	if (g_pad[0]->IsPress(enButtonB))
	{
		m_moveSpeed.x *= 2.0f;
		m_moveSpeed.z *= 2.0f;
	}

	
	ManageJumpState();
	

	////���X�|�[��
	//if (m_position.y <= -100.0f)
	//{
	//	m_position = m_RePosition;
	//	m_moveSpeed = Vector3::Zero;
	//	m_characterController.SetPosition(m_position);
	//}

	
	


	//�L�����R���ňړ�
	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	m_modelRender.SetPosition(m_position);
}

//��]����
void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);

		m_modelRender.SetRotation(m_rotation);
	}
}

//�v���C���[�̃X�e�[�g����
void Player::ManagePlayerState()		//�X�e�[�g����
{
	if (m_characterController.IsOnGround() == false) {
		m_playerState = enState_Jump;
		return;
		//�����n�ʂɂ��Ă��Ȃ�������v���C���[�̃X�e�[�g��enState_Jump�ɂ���
	}

	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f){
		m_playerState = enState_Walk;
		//�����X�e�B�b�N�̓��͂���������v���C���[�̃X�e�[�g��enState_Walk�ɂ���
		
		if (g_pad[0]->IsPress(enButtonB)) {
			m_playerState = enState_Run;
		}
		//�����ړ�����B�{�^���������ꂽ��v���C���[�̃X�e�[�g��enState_Run�ɂ���
	}

	else {
		m_playerState = enState_Idle;
		//�����������Ă��Ȃ�������v���C���[�̃X�e�[�g��enState_Idle�ɂ���
	}
}

void Player::ManageJumpState()
{
	
	//�n�ʂɂ��Ă�����
	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;//�d�͂��Ȃ���
		m_jumpCount = 0;
	}
	//�n�ʂɂ��Ă��Ȃ�������
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
		//�W�����v������
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
	//���f����\������
	m_modelRender.Draw(renderContext);
}