#pragma once

class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	//�������烁���o�ϐ�
	Player* m_player;
	Vector3 m_toCameraPos;
};

