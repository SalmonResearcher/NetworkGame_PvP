#pragma once
#include"IPlayer.h"
#include"Engine/GameObject.h"
#include"PlayerMethod.h"

class Player : public IPlayer , public GameObject
{
public:
	Player();
	Player(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

protected:

	uint8_t modelnum_;

	State state_;

	SphereCollider* col;
};

