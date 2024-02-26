#include "Timer.h"

static const int FPS = 60;

Timer::Timer(GameObject* obj) : GameObject(obj, "Timer"),
    pText(nullptr), frame(0), active(false), drawX(0), drawY(0)
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

		if (frame == 0)
		{
			pText->Draw(30, 30, "GAME OVER");
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
	//delete pText;
}

void Timer::SetLimit(float seconds)
{
	frame = 120 * (int)(seconds * FPS);
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