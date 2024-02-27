#include "PlayScene.h"
#include "Engine/Camera.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
	ground = Model::Load("Ground.fbx");

	Camera::SetPosition({ 0,6,-9.5 });
}

void PlayScene::Initialize()
{
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
	Transform trans = {};
	trans.rotate_.y = 180;
	trans.scale_ = { .8f,.8f,.8f };

	Model::SetTransform(ground, trans);
	Model::Draw(ground);
}

void PlayScene::Release()
{
}
