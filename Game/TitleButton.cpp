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

	//タイトル画面で何かボタンが押されたら
	if (m_buttonPos == enButtonPos_Not) {
		if (g_pad[0]->IsPressAnyKey()) {
			//点滅位置をStartにし、フェードをInにする
			m_buttonPos = enButtonPos_Start;
			m_fadeState = enFadeState_In;
		}
	}

	//何かしらが選択されていたら
	if (m_buttonPos != enButtonPos_Not) {
		//フェードステートがInなら
		if (m_fadeState == enFadeState_In) {
			m_transPar += m_fadeSpeed;
			if (m_transPar >= 1.0f) {
				m_transPar = 1.0f;
				m_fadeState = enFadeState_Out;
			}
		}
		//フェードステートがOutなら
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