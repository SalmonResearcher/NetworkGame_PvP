#include "Timer.h"
#include "Engine/Input.h"

Timer::Timer(GameObject* obj) : GameObject(obj, "Timer"),
    pText(nullptr), frame(0), active(false), drawX(600), drawY(30), limitFrame(0)
{
}

Timer::~Timer()
{
}

void Timer::Initialize()
{
	pText = new Text;
	pText->Initialize();

	frame = 0;
	active = false;

	SetLimit(120); //制限時間を設定
}

void Timer::Update()
{
	Start();

	if (active) {
		if (frame > 0) {
			frame--;
		}
	}

	Stop();

	IsFinished();
}

void Timer::Draw()
{
	pText->SetScale(1.0f);

	//if (frame % FPS < 10)
	//	pText->SetScale((frame % FPS) * 0.2f + 1.0f);
	//else
	//	pText->SetScale(1.0f);

	int sec = frame / FPS; //経過した秒数を計算
	std::string timeString = std::to_string(sec / 60) + ":" + std::to_string(sec % 60); //分:秒の文字列を作成
	pText->Draw(drawX, drawY, timeString.c_str());
}

void Timer::Release()
{
	//pText->Release();
}

void Timer::SetLimit(float seconds)
{
	limitFrame = FPS * seconds;
	frame = limitFrame;
}

void Timer::Start()
{
	active = true;
}

void Timer::Stop()
{
	active = false;
}

bool Timer::IsFinished()
{
	return (frame == 0);
}