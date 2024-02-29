#pragma once
#include "Engine/GameObject.h"

class Player;

//テストシーンを管理するクラス
class TestScene : public GameObject
{
	Player* pPlayer1;
	Player* pPlayer2;
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TestScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};