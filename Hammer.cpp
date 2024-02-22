#include "Hammer.h"
#include "Engine/Model.h"

Hammer::Hammer(GameObject* parent) :hModel_(-1)
{
}

void Hammer::Initialize()
{
	hModel_ = Model::Load("Hammer_Anime.fbx");
	assert(hModel_ >= 0);
}

void Hammer::Update()
{
}

void Hammer::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Hammer::Release()
{
}

void Hammer::Animation(int start, int end, int speed)
{
	Model::SetAnimFrame(hModel_, start, end, speed);
}