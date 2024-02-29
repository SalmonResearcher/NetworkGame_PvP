#include "IPlayer.h"


IPlayer::IPlayer()
{
	comp = {};
}

void IPlayer::Run()
{
	stt->Run();

	atk->Run();
	dif->Run();
	jmp->Run();
}

IPlayer::SPlayerComp::SPlayerComp():size(1,1,1), Anim(0, 0, 0), CID(0), PID(0), model(0), val0(0), val1(0), val2(0), val3(0)
{
}
