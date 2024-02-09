#pragma once
#include<cstdint>

class IAttack
{
public:

	void AttackTo(int PID);//指定したプレイヤーに攻撃

	struct AttackComp_SEND
	{
		float force;
		float knock;
		float speed;

		uint8_t toPID;//攻撃するPlayer ID
		uint8_t fromPID;//自身のPlayerI D

		float val0, val1, val2, val3;
	}comp;

	struct AttackComp_RECV
	{

	};

	//need collider
};