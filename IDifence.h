#pragma once
#include<cstdint>

class IDifence
{
public:
	struct DifenceComp
	{
		float difence;

		float val0, val1, val2, val3;
	}comp;

	virtual void Difence() = 0;

private:

	virtual void Run() = 0;
};

