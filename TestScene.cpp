#include "TestScene.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	bk = Image::Load("BackGround.png");
	title = Image::Load("Title.png");
	select = Image::Load("Select.png");
	exit = Image::Load("Exit.png");
	enter = Image::Load("Play.png");
}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
	Transform t = {};
	t.position_ = { 0,0,0 };
	t.scale_ = { 2.5,1.5,0 };
	Image::SetTransform(bk,t );
	Image::Draw(bk);

	t.position_ = { 0,.4f,0 };
	t.scale_ = { 0.4,0.4,0 };
	Image::SetTransform(title, t);
	Image::Draw(title);

	t.position_ = { 0,0,0 };
	t.scale_ = { .5,1,0 };
	Image::SetTransform(select, t);
	Image::Draw(select);
}

//開放
void TestScene::Release()
{
}
