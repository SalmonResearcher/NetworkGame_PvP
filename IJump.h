#pragma once
#include"MACRO.h"

class IJump
{
public :

	virtual void Jump() = 0;
	virtual void Run() = 0;


	struct JumpComp
	{
		Position pos;
		Rotation rot;
		
		XMFLOAT3 vec;
		float speed;

		float val0, val1, val2, val3;
	};

private:

};

