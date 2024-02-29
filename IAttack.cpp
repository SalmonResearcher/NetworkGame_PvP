#include "IAttack.h"

IAttack::IAttack(IPlayer* p):parent(p)
{
	comp = {};
}

IAttack::AttackComp::AttackComp() :force(0), knock(0), speed(0), cool(0), ray(1, 0, 0)
{
}
