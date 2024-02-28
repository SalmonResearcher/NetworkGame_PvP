#pragma once
#include"IPlayer.h"
#include"Engine/GameObject.h"

class Player : public IPlayer , public GameObject
{
public:
	Player();
	void Update() override;

	void Initialize(void);
	void Update(void);
	void Draw();
	void Release(void);

protected:

	uint8_t modelnum_;

};

