#pragma once
#include<cstdint>
#include"Engine/Collider.h"

class IPlayer;

class IAttack
{
public:

	virtual void Attack() = 0;


	struct AttackComp
	{
		float force;
		float knock;
		float speed;
		float cool;

		float val0, val1, val2, val3;
	}comp;
	virtual void Run() = 0;

	IAttack(IPlayer* p);

protected:

	IPlayer* parent;

};

