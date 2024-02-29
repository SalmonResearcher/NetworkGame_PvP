#pragma once
#include<cstdint>

class IPlayer;

class IState
{
public:
	IState() = default;
	IState(IPlayer* p);

	enum class Mask
	{
		Immovable			= 1,
		Healing				= Immovable * 2,
		WScore				= Healing * 2,
		Death				= WScore * 2,
		Landing				= Death * 2,
		Running				= Landing *2,


	};

	struct StateComp
	{
		StateComp();
		uint8_t sttbit;

		float val0, val1, val2, val3;
	}comp;

	virtual void Run() = 0;


protected:

	IPlayer* parent;

};

