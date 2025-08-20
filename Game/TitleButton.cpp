#include "stdafx.h"
#include "TitleButton.h"

TitleButton::TitleButton()
{
	
}

TitleButton::~TitleButton()
{

}

bool TitleButton::Start()
{
	m_spriteRenderStart.Init("Assets/Sprite/StartButton.dds", 1920.0f, 1080.0f);
	m_spriteRenderHowToPlay.Init("Assets/Sprite/HowToPlay.dds", 1920.0f, 1080.0f);

	m_fadeState = enFadeState_Stay;
	return true;
}

void TitleButton::Update()
{
	Font();
}

void TitleButton::Font()
{

	//�^�C�g����ʂŉ����{�^���������ꂽ��
	if (m_buttonPos == enButtonPos_Not) {
		if (g_pad[0]->IsPressAnyKey()) {
			//�_�ňʒu��Start�ɂ��A�t�F�[�h��In�ɂ���
			m_buttonPos = enButtonPos_Start;
			m_fadeState = enFadeState_In;
		}
	}

	//�������炪�I������Ă�����
	if (m_buttonPos != enButtonPos_Not) {
		//�t�F�[�h�X�e�[�g��In�Ȃ�
		if (m_fadeState == enFadeState_In) {
			m_transPar += m_fadeSpeed;
			if (m_transPar >= 1.0f) {
				m_transPar = 1.0f;
				m_fadeState = enFadeState_Out;
			}
		}
		//�t�F�[�h�X�e�[�g��Out�Ȃ�
		if (m_fadeState == enFadeState_Out) {
			m_transPar -= m_fadeSpeed;
			if (m_transPar <= 0.0f) {
				m_transPar = 0.0f;
				m_fadeState = enFadeState_In;
			}
		}
	}

	if (m_buttonPos == enButtonPos_Start) {
		m_spriteRenderStart.SetMulColor({ 0.0f, 0.0f, 1.0f, m_transPar });
		m_spriteRenderHowToPlay.SetMulColor({ 0.0f, 0.0f, 1.0f, 1.0f });
		if (g_pad[0]->IsTrigger(enButtonDown)) {
			m_buttonPos = enButtonPos_HowToPlay;
		}
	}

	if (m_buttonPos == enButtonPos_HowToPlay) {
		m_spriteRenderHowToPlay.SetMulColor({ 0.0f, 0.0f, 1.0f, m_transPar });
		m_spriteRenderStart.SetMulColor({ 0.0f, 0.0f, 1.0f, 1.0f });
		if (g_pad[0]->IsPress(enButtonUp)) {
			m_buttonPos = enButtonPos_Start;
		}
	}
	
	
}


void TitleButton::Render(RenderContext& rc)
{
	m_spriteRenderStart.Draw(rc);
	m_spriteRenderHowToPlay.Draw(rc);
}