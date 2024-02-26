#pragma once
#include<cstdint>

class IState
{
public:

	enum class Mask
	{
		Immovable = 1,
		Healing = Immovable * 2,
		WScore = Healing *2,
		Death = WScore *2,
	};

	struct StateComp
	{
		uint8_t sttbit;

		float val0, val1, val2, val3;
	};

	virtual void State() = 0;

private:

	virtual void Run() = 0;
};

