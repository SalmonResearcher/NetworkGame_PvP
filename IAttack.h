#pragma once
#include<cstdint>

class IAttack
{
public:

	void AttackTo(int PID);


	struct AttackComp
	{
		float force;
		float knock;
		float speed;

		uint8_t toPID;
		uint8_t fromPID;

		float val0, val1, val2, val3;
	}comp;

	//need collider
};

