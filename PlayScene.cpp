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
	//PID_NUM get;

	for (auto i = 0u; i < PLAYER_AMOUNT; ++i) {

		pl[i] = Instantiate<Player>(this);
	}
}

void PlayScene::Update()
{
	//memcpy(pl, ConnectComp, sizeof(IPlayer::SPlayerComp) * PLAYER_AMOUNT);

	pl[PID_NUM]->SingleUpdate();

	SendComp(PID_NUM);
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

void PlayScene::SendComp(uint8_t myID)
{
	pl[myID];
}
