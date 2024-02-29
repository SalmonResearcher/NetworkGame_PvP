#include "TestScene.h"
#include "Player.h"
#include "Stage.h"
#include "Engine/Camera.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Instantiate<Player>(this);
	Instantiate<Stage>(this);

	//�J�����ʒu���Ă��Ƃ��ɔz�u
	Camera::SetPosition({0,10,-25});
	Camera::SetTarget({ 0,0,0 });
}

//�X�V
void TestScene::Update()
{
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
