#pragma once
class Game;
class TitleButton;
class Title:public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	
	TitleButton* m_titleButton = nullptr;
	SpriteRender m_spriteRender;
};

