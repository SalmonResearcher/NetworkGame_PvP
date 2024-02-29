#pragma once
#include "Engine/GameObject.h"
#include<cstdint>
#include"Engine//Model.h"
#include"Player.h"

constexpr uint8_t PLAYER_AMOUNT = 2;

class PlayScene : public GameObject
{
public:
	PlayScene(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

private:
	Player* pl[PLAYER_AMOUNT];

	uint8_t ground;
};