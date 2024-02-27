#include "Timer.h"

Timer::Timer(GameObject* obj) : GameObject(obj, "Timer"),
    pText(nullptr), frame(0), active(false), drawX(30), drawY(30), limitFrame(0)
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
}

void Timer::Update()
{
	if (active) {
		if (frame > 0) {
			frame--;
		}
	}
}

void Timer::Draw()
{
	pText->SetScale(1.0f);
	pText->SetColor(255, 255, 255);
	pText->Draw(drawX, drawY, "Time");

	if (frame % FPS < 10)
		pText->SetScale((frame % FPS) * 0.2f + 1.0f);
	else
		pText->SetScale(1.0f);

	int sec = frame / FPS;
	std::string timeString = std::to_string(sec / 60) + ":" + std::to_string(sec % 60);
	pText->Draw(drawX + 150, drawY, timeString.c_str());
}

void Timer::Release()
{
	pText->Release();
}

void Timer::SetLimit(float seconds)
{
	limitFrame = FPS * 120 * seconds;
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