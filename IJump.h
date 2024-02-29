#pragma once
#include"MACRO.h"

class IJump
{
public :

	virtual void Jump() = 0;
	virtual void Run() = 0;


	struct JumpComp
	{
		Position pos;//Œ»İ‚ÌêŠ
		Rotation rot;
		Position vec;//ˆÚ“®‚µ‚½‚¢•ûŒüƒxƒNƒgƒ‹
		float speed;//ã‚Ö‚ÌˆÚ“®

		float val0, val1, val2, val3;

		JumpComp();
	}comp;
private:

};

