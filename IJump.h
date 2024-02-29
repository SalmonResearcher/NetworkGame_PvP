#pragma once
#include"MACRO.h"


class IPlayer;

class IJump
{
public :
	IJump() = default;
	IJump(IPlayer* p);


	virtual void Jump() = 0;
	virtual void Run() = 0;


	struct JumpComp
	{

		Position pos;
		Rotation rot;
		
		Position vec;
		float speed;


		float val0, val1, val2, val3;

		JumpComp();
	}comp;

protected:

	IPlayer* parent;

};

