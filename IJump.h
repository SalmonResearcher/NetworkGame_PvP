#pragma once
#include"MACRO.h"

class IJump
{
public :

	virtual void Jump() = 0;
	virtual void Run() = 0;


	struct JumpComp
	{
		Position pos;//���݂̏ꏊ
		Rotation rot;
		Position vec;//�ړ������������x�N�g��
		float speed;//��ւ̈ړ�

		float val0, val1, val2, val3;

		JumpComp();
	}comp;
private:

};

