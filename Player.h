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

	bool IsPlayable() {}

	CliantPlayer pla;

};

