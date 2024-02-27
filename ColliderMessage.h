#pragma once
#include<cstdint>
#include"MACRO.h"

constexpr uint8_t MAX_COLLIDER_AMOUNT = 10;

struct ColliderInfo
{
	Position pos;
	Rotation rot;
	Scale size;

	uint8_t type;
};

struct ColliderMessage
{
	uint8_t cnt;// amount of collider
	uint8_t parent;
	ColliderInfo info[MAX_COLLIDER_AMOUNT];
};

