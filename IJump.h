#pragma once
#include"MACRO.h"

class IJump
{
public :

	virtual void Jump() = 0;
	virtual void Run() = 0;


	struct JumpComp
	{
		Position pos;//現在の場所
		Rotation rot;
		Position vec;//移動したい方向ベクトル
		float speed;//上への移動

		float val0, val1, val2, val3;

		JumpComp();
	}comp;
private:

};

