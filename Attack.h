#pragma once
#include<cstdint>

class IAttack
{
public:

	void AttackTo(int PID);//�w�肵���v���C���[�ɍU��

	struct AttackComp_SEND
	{
		float force;
		float knock;
		float speed;

		uint8_t toPID;//�U������Player ID
		uint8_t fromPID;//���g��PlayerI D

		float val0, val1, val2, val3;
	}comp;

	struct AttackComp_RECV
	{

	};

	//need collider
};