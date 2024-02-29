#include "Player.h"
#include "Engine/Model.h"
#include"Engine/SphereCollider.h"

constexpr float radius = .5f;

Player::Player() :state_(this)
{
}

Player::Player(GameObject* parent):GameObject(parent),state_(this)
{
}

void Player::Initialize(void)
{
	modelnum_ = Model::Load("Player.fbx");
	stt = &state_;
}

void Player::Update()
{
}

void Player::Draw()
{
	Transform trans = {};
	trans.position_ = comp.s_jmp.pos;
	//trans.position_.y = 0;

	trans.rotate_ = comp.s_jmp.rot;
	//trans.rotate_ = {0,0,0};

	trans.scale_ = comp.size;
	//trans.scale_ = { 1,1,1 };

	Model::SetTransform(modelnum_, trans);
	Model::Draw(modelnum_);
}

void Player::Release(void)
{
}

void Player::SingleUpdate()
{
	Run();

	{
		comp.pc.pos = comp.s_jmp.pos;
		comp.pc.rot = {};
		comp.pc.size = { radius , radius , radius };
		comp.pc.type = static_cast<uint8_t>(ColliderContext::CC_Player);
	}
}
