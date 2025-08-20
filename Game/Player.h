#pragma once
class Player : public IGameObject
{
public:
	Player();
	~Player();
	void Update();					//�X�V����
	void Render(RenderContext& renderContext);		//�`�揈��
	void Move();		//�ړ�����
	void Rotation();	//��]����
	void ManagePlayerState();	//�X�e�[�g�Ǘ�
	void ManageJumpState();		//�V�������֐��i�W�����v�X�e�[�g�֐��j
	void PlayAnimation();
	

	enum EnAnimation {
		enAnimationClip_Idle,
		enAnimationClip_Jump,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Num
	};

	enum EnPlayerState {
		enState_Idle,
		enState_Jump,
		enState_Walk,
		enState_Run,
		enState_Num
	};

	//�������烁���o�ϐ�
	ModelRender m_modelRender;
	CharacterController m_characterController;
	Quaternion m_rotation; //�N�I�[�^�j�I��
	Vector3 m_moveSpeed;
	Vector3 m_dashSpeed;
	Vector3 m_position;		//���W
	float m_gravity = 9.8 * 2.5f;
	bool m_jump = true;
	int m_jumpCount = 0;	
	int m_maxJumpCount = 2;	
	int m_playerState = 0;
	AnimationClip m_animationClips[enAnimationClip_Num];

};

