#pragma once
#include "Engine/GameObject.h"

class IPlayer;
class Server;

class Player :
    public GameObject
{
private:
	int hModel_;
	struct CliantPlayer
	{
		Transform transPlayer_;
	};

	IPlayer* pID;

	Server* pServer;
	int listen = 0;
	int sock = 0;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	bool IsPlayable() {}

	CliantPlayer pla;

};

