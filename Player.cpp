#include "Player.h"
#include "Hammer.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "TestScene.h"
#include "Server.h"

Player::Player(GameObject* parent):hModel_(-1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("TestPlayer.fbx");
	assert(hModel_ >= 0);
	
	Instantiate<Hammer>(this);

	listen = pServer->InitWinSock();
	sock = pServer->UDPSock();
}

void Player::Update()
{
	if (isPlayable)
	{
		if (Input::IsKey(DIK_W)) {
			pla.transPlayer_.position_.z += 0.1;
		}

		if (Input::IsKey(DIK_S)) {
			pla.transPlayer_.position_.z -= 0.1;
		}

		if (Input::IsKey(DIK_D)) {
			pla.transPlayer_.position_.x += 0.1;
		}

		if (Input::IsKey(DIK_A)) {
			pla.transPlayer_.position_.x -= 0.1;
		}
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel_, pla.transPlayer_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}
