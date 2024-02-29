#include "IJump.h"

IJump::JumpComp::JumpComp() :pos(0, 0, 0), rot(0, 0, 0), vec(0, 0, 0),speed(0)
{
}

IJump::IJump(IPlayer* p):parent(p)
{
}
