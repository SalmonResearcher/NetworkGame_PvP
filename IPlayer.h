#pragma once
#include<DirectXMath.h>

using DirectX::XMFLOAT3;

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

	struct PlayerComp
	{
		PlayerComp();

		XMFLOAT3 pos;
		uint32_t Anim;
		uint32_t model;

		uint8_t CID;
		uint8_t PID;

		float val0;
		float val1;
		float val2;
		float val3;
		//----------add some component whene neccesary

	}comp;
};

