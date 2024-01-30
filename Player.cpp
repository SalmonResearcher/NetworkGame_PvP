#include "Player.h"
#include "Engine/Model.h"

Player::Player(GameObject* parent):hModel_(-1)
{
}

void Player::Initialize()
{
	hModel_ = Model::Load("TestPlayer.fbx");
	assert(hModel_ >= 0);
}

void Player::Update()
{

}

void Player::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Player::Release()
{
}
