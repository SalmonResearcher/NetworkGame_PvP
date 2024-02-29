#include "IState.h"

IState::IState(IPlayer* p):parent(p)
{
}

IState::StateComp::StateComp()
{
	sttbit = static_cast<uint32_t>(Mask::Landing);
}
