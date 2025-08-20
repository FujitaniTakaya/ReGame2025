#pragma once
class Title;

class GameOver:public IGameObject
{
public:
	GameOver();
	~GameOver();
	void Update();
	void Render(RenderContext& rc);

	
	SpriteRender m_spriteRender;
};

