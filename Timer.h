#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

static const int FPS = 60;

class Timer : public GameObject
{
private:
	int frame;
	int limitFrame;
	int drawX, drawY; //XÇ∆YÇÃà íuç¿ïW
	bool active;      //ìÆÇ¢ÇƒÇÈÇ©Ç«Ç§Ç©

	Text* pText;
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
};