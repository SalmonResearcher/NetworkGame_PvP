#pragma once
#include "Engine/GameObject.h"



class Player :
    public GameObject
{
private:
	int hModel_;
	struct CliantPlayer
	{
		Transform transPlayer_;
	};

protected:
	//構造体
	struct PlayerStates {
		//Player* pPlayer;
		int8_t PlayerID;
		int hp_;
		Transform* pPlayerPos;
	};

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	

	CliantPlayer pla;

};

