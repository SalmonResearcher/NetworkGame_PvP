#pragma once
#include<DirectXMath.h>
#include "IAttack.h"
#include "IDifence.h"
#include "IJump.h"
#include "IState.h"
#include "MACRO.h"

using namespace DirectX;

class IAttack;
class IJump;
class IState;
class IDifence;

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

		XMFLOAT3 size;

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

	}comp;

	struct GPlayerComp	//get from server
	{
		XMFLOAT3 size;

	}recv;

	virtual void Update() = 0;

public:


private:
	void Run();


private:

};

