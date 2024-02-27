#pragma once
#include "Engine/GameObject.h"
#include<cstdint>
#include"Engine//Model.h"

constexpr uint8_t PLAYER_AMOUNT = 4;

class PlayScene : public GameObject
{
public:
	PlayScene(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

private:
	uint8_t players_model[PLAYER_AMOUNT];

	uint8_t ground;
};