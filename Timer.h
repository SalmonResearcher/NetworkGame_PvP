#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

static const int FPS = 60;

class Timer : public GameObject
{
public:
	Timer(GameObject* obj);
	~Timer();

	void Initialize();
	void Update();
	void Draw();
	void Release();

	void SetLimit(float seconds);
	void Start();
	void Stop();
	bool IsFinished();

private:
	int frame;
	int limitFrame;
	int drawX, drawY;
	bool active;

	Text* pText;
};