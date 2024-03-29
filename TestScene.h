#pragma once
#include "Engine/GameObject.h"
#include"Engine/Image.h"
#include"Engine/SceneManager.h"
#include"MACRO.h"

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

private:

	uint8_t bk;
	uint8_t title;
	
	uint8_t select;

	uint8_t exit;
	uint8_t enter;

	enum SM
	{
		play,
		end,
	};
	uint8_t selectionMode;
	Position pos;
};