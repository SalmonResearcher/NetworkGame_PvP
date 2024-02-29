#pragma once
#include<cstdint>

class IPlayer;

class IDifence
{
public:
	IDifence(IPlayer* p);
	IDifence() = default;

	struct DifenceComp
	{
		float difence;
		float gauge;
		float consume;
		float val0, val1, val2, val3;
	}comp;

	virtual void Difence() = 0;
	virtual void Run() = 0;
  
protected:
	IPlayer* parent;


};

