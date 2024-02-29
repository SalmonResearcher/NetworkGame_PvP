#include "TestScene.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	bk = Image::Load("BackGround.png");
	title = Image::Load("Title.png");
	select = Image::Load("Select.png");
	exit = Image::Load("Exit.png");
	enter = Image::Load("Play.png");
}

//�X�V
void TestScene::Update()
{
}

//�`��
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

//�J��
void TestScene::Release()
{
}
