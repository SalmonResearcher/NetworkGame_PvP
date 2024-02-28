#include "Player.h"
#include "Engine/Model.h"

Player::Player()
{
}

void Player::Initialize(void)
{
	modelnum_ = Model::Load("Player.fbx");

}

void Player::Update()
{
	comp.pc.pos = this->comp.s_jmp.pos;

	Run();
}

void Player::Draw()
{
	Transform trans = {};
	trans.position_ = comp.s_jmp.pos;
	trans.rotate_ = comp.s_jmp.rot;
	trans.scale_ = comp.size;

	Model::SetTransform(modelnum_, trans);
	Model::Draw(modelnum_);
}

void Player::Release(void)
{
}
