#include "TestScene.h"
#include "Player.h"
#include "Stage.h"
#include "Engine/Camera.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<Player>(this);
	Instantiate<Stage>(this);

	//カメラ位置をてきとうに配置
	Camera::SetPosition({0,10,-25});
	Camera::SetTarget({ 0,0,0 });
}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
