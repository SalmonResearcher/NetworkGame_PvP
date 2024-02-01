#pragma once
#include<DirectXMath.h>

using DirectX::XMFLOAT3;

class IAttack;
class IJump;
class IState;

class IPlayer
{
public:
	IPlayer();

	IAttack* atk;
	IJump* jmp;
	IState* stt;

	struct PlayerComp
	{
		XMFLOAT3 pos;
		uint32_t Anim;
		uint32_t model;

		//----------add some component whene neccesary

	}comp;
};

