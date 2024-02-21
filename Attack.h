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
		float range;

		uint8_t toPID;   //攻撃するPlayerID
		uint8_t fromPID; //自身のPlayerID

		float val0, val1, val2, val3;
	}comp;

	struct AttackComp_RECV
	{
		float force;
		float knock;
		float speed;
		float range;

		uint8_t toPID;   //攻撃するPlayerID
		uint8_t fromPID; //自身のPlayerID

		float val0, val1, val2, val3;
	}recv_comp;

	//need collider
	struct Collider_SEND {
		float positionX;
		float positionY;
		float width;
		float height;
	}collider;

	struct Collider_RECV {
		float positionX;
		float positionY;
		float width;
		float height;
	}recv_collider;

	void InitCollider(float posX, float posY, float width, float height);

	bool isCollide(const Collider& collide);
};