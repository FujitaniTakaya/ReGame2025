#pragma once

//�w�i
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	void Render(RenderContext& rc);

	ModelRender m_modelRender;		//���f�������_�[
	PhysicsStaticObject m_physicsStaticObject;
};