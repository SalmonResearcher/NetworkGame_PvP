#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

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
	Text* num;
	bool active;
	int drawX;
	int drawY;
};