#include "Stage.h"
#include "Engine/Model.h"

Stage::Stage(GameObject* parent) :hModel_(-1)
{
}

void Stage::Initialize()
{
	hModel_ = Model::Load("TestStage.fbx");
	assert(hModel_ >= 0);
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Stage::Release()
{
}