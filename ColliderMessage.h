#pragma once
#include<cstdint>
#include"MACRO.h"

constexpr uint8_t MAX_COLLIDER_AMOUNT = 10;

enum ColliderContext
{
	CC_Player,
	CC_Attack,
};

struct ColliderInfo
{
	ColliderInfo();

	Position pos;
	Rotation rot;
	Scale size;

	uint8_t type;
};

struct ColliderMessage
{
	ColliderMessage();

	uint8_t cnt;// amount of collider
	uint8_t parent;
	ColliderInfo info[MAX_COLLIDER_AMOUNT];
};

