#pragma once

//”wŒi
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	void Render(RenderContext& rc);

	ModelRender m_modelRender;		//ƒ‚ƒfƒ‹ƒŒƒ“ƒ_[
	PhysicsStaticObject m_physicsStaticObject;
};