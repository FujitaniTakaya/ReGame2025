#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	//“–‚½‚è”»’è‚Ì•`‰æ
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	m_modelRender.Init("Assets/modelData/Stage/stage.tkm");

	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

BackGround::~BackGround()
{

}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}