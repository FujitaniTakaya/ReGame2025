#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "TitleButton.h"
Title::Title()
{
	m_titleButton = FindGO<TitleButton>("titleButton");
}

Title::~Title()
{
	DeleteGO(m_titleButton);
}

bool Title::Start()
{
	m_spriteRender.Init("Assets/Sprite/Title.dds", 1920.0f, 1080.0f);
	m_titleButton = NewGO<TitleButton>(0, "titleButton");

	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonX)) {
		NewGO<Game>(0, "game");
		DeleteGO(this);
	}

}

void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}