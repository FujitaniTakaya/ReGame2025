#include "stdafx.h"
#include "GameCamera.h"
#include "player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�
	m_toCameraPos.Set(0.0f, 125.0f, -250.0f);
	//�v���C���[�̃C���X�^���X��T��
	m_player = FindGO<Player>("battleCharacter");

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��
	g_camera3D->SetNear(10.0f);
	g_camera3D->SetFar(100000.0f);

	return true;
}

void GameCamera::Update()
{
	//�J�������X�V
	//�����_���v�Z����
	Vector3 target = m_player->m_position;
	//�v���C���[�̑������炿����Ə�𒍎��_�Ƃ���
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_toCameraPos;
	//�p�b�h�̓��͂��g���ăJ��������
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y������̊J�X
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
	qRot.Apply(m_toCameraPos);
	//X������̉�]
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.3f * y);
	qRot.Apply(m_toCameraPos);
	
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.2f)
	{
		//�J������������
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f)
	{
		//�J������������
		m_toCameraPos = toCameraPosOld;
	}

	//���_���v�Z����
	Vector3 pos = target + m_toCameraPos;
	//���C���J�����ɒ����_�Ǝx�X��ݒ肷��
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	g_camera3D->Update();
}

