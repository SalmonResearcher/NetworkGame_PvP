#pragma once
#include<DirectXMath.h>
#include "IAttack.h"
#include "IDifence.h"
#include "IJump.h"
#include "IState.h"
#include "MACRO.h"

#include "ColliderMessage.h"

using namespace DirectX;

class IAttack;
class IJump;
class IState;
class IDifence;


constexpr int MAX_HP = 100;

class IPlayer
{
public:
	IPlayer();

	IAttack* atk;
	IDifence* dif;
	IJump* jmp;
	IState* stt;

	struct SPlayerComp	//send to server
	{
		SPlayerComp();

		int HP;

		Scale size;

		AnimScene Anim;
		uint32_t model;

		uint8_t CID;
		uint8_t PID;

		float val0;
		float val1;
		float val2;
		float val3;

		//----------add some component when neccesary
		IAttack::AttackComp s_atk;
		IDifence::DifenceComp s_dif;
		IJump::JumpComp s_jmp;
		IState::StateComp s_stt;

		ColliderMessage msg;
		ColliderInfo pc;
	}comp;

public:


protected:
	virtual void Run();



private:

};

