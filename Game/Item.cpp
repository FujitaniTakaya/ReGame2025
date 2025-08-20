#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "GameClear.h"

Item::Item()
{
	m_modelRender.Init("Assets/modelData/Item.tkm");
	g_soundEngine->ResistWaveFileBank(0, "Assets/Sound/ItemGet.wav");

	m_player = FindGO<Player>("battleCharacter");	
}

Item::~Item()
{

}

void Item::Update()
{
	//ˆÚ“®ˆ—
	Move();
	//‰ñ“]ˆ—
	Rotation();


	Vector3 diff = m_player->m_position - m_position;

	if (diff.Length() <= 40.0f) {

		m_getSE = NewGO<SoundSource>(0);
		m_getSE->Init(0);
		m_getSE->Play(false);
		m_getSE->SetVolume(3.5f);
		DeleteGO(this);
		m_itemCount++;
	}

	

	m_modelRender.Update();
}

void Item::Move()
{
	if (m_moveState == enMoveState_Up) {
		m_position.y += 1.0f;
	}

	if (m_moveState == enMoveState_Down) {
		m_position.y -= 1.0f;
	}

	if (m_position.y >= m_firstPosition.y + 20.0f) {
		m_moveState = enMoveState_Down;
	}

	else if (m_position.y <= m_firstPosition.y -20.0f) {
		m_moveState = enMoveState_Up;
	}

	m_modelRender.SetPosition(m_position);
}

void Item::Rotation()
{
	m_rotation.AddRotationDegY(2.0f);

	m_modelRender.SetRotation(m_rotation);
}

void Item::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}