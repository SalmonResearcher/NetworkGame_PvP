#include "TestScene.h"
#include "Timer.h"

#include"Engine/Input.h"



//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<Timer>(this);
	bk = Image::Load("BackGround.png");
	title = Image::Load("Title.png");
	select = Image::Load("Select.png");
	exit = Image::Load("Exit.png");
	enter = Image::Load("Play.png");

	pos = { 0,0,0 };

}

//更新
void TestScene::Update()
{
	if (Input::IsKeyDown(DIK_W) || Input::IsKeyDown(DIK_S))
	{
		selectionMode++;
		selectionMode%= 2;
	}

	if (selectionMode == SM::end)
	{
		pos = { 0,-0.5,0 };
		if (Input::IsKeyDown(DIK_RETURN))	std::exit(0);
	}

	else
	{
		pos = { 0,-0.1,0 };
		if (Input::IsKeyDown(DIK_RETURN))
		{
			SceneManager* sm = (SceneManager*)FindObject("SceneManager");

			sm->ChangeScene(SCENE_ID_PLAY);
		}
	}

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

	t.position_ = pos;
	t.scale_ = { .5,.1,0 };
	Image::SetTransform(select, t);
	Image::Draw(select);

	t.position_ = { 0,-.1f,0 };
	t.scale_ = { 0.2,0.2,0 };
	Image::SetTransform(enter, t);
	Image::Draw(enter);

	t.position_ = { 0,-.5f,0 };
	t.scale_ = { 0.2,0.2,0 };
	Image::SetTransform(exit, t);
	Image::Draw(exit);
}

//開放
void TestScene::Release()
{
}
