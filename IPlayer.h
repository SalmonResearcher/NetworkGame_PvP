#pragma once
#include<DirectXMath.h>
#include "IAttack.h"
#include "IDifence.h"
#include "IJump.h"
#include "IState.h"

using namespace DirectX;

typedef XMFLOAT3 Position;
typedef XMFLOAT3 Rotation;
typedef XMFLOAT3 Scale;
typedef XMFLOAT3 AnimScene;

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

	struct SPlayerComp
	{
		SPlayerComp();

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

	}comp;

public:


private:


private:

};

