#pragma once
class TitleButton:public IGameObject
{
public:
	TitleButton();
	~TitleButton();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Font();

	enum EnButtonPos {
		enButtonPos_Not,
		enButtonPos_Start,
		enButtonPos_HowToPlay,
		enButtonPos_Num
	};


	enum EnFadeState {
		enFadeState_Stay,
		enFadeState_In,
		enFadeState_Out,
		enFadeState_Num
	};

	SpriteRender m_spriteRenderStart;
	SpriteRender m_spriteRenderHowToPlay;

	bool m_startFade = false;	
	bool m_howToPlayFade = false;
	const float m_fadeSpeed = 0.01f;
	float m_transPar;				//“§–¾“x
	int m_fadeState = enFadeState_Stay;
	int m_buttonPos = enButtonPos_Start;
};

