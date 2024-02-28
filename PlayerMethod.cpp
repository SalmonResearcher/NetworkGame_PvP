#include "PlayerMethod.h"
#include"IPlayer.h"

DashAttack::DashAttack(IPlayer* p):IAttack(p)
{
}

void DashAttack::Run()
{
	comp = {};
	if (Input::IsKeyDown(DIK_RETURN)) Attack();
}

void DashAttack::Attack()
{
	parent->comp.msg.info[parent->comp.msg.cnt].pos = parent->comp.s_jmp.pos;

	comp.cool = 12;
	comp.force = 8;
	comp.speed = 12;
	comp.knock = .2f;
}

JumpAttack::JumpAttack(IPlayer* p) :IAttack(p)
{
}

void JumpAttack::Run()
{
	comp = {};
	if (Input::IsKeyDown(DIK_RETURN)) Attack();
}

void JumpAttack::Attack()
{
	parent->comp.msg.info[parent->comp.msg.cnt].pos = parent->comp.s_jmp.pos;

	comp.cool = 40;
	comp.force = 20;
	comp.speed = 6;
	comp.knock = 2.0f;
}

NeutralAttack::NeutralAttack(IPlayer* p) :IAttack(p)
{
}

void NeutralAttack::Run()
{
	comp = {};
	if (Input::IsKeyDown(DIK_RETURN)) Attack();
}

void NeutralAttack::Attack()
{
	parent->comp.msg.info[parent->comp.msg.cnt].pos = parent->comp.s_jmp.pos;

	comp.cool = 3;
	comp.force = 7;
	comp.speed = 4;
	comp.knock = .04f;
}

//--------------------------------------------

void DashDifence::Difence()
{
	comp.difence = 4;
	comp.consume = .5f;
}

void DashDifence::Run()
{
	if (Input::IsKey(DIK_LSHIFT))	Difence();

	else
	{
		comp.difence = 0;
		comp.consume = -0.1;
	}
}

void JumpDifence::Difence()
{
	comp.difence = 10;
	comp.consume = 1.0f;
}

void JumpDifence::Run()
{
	if (Input::IsKey(DIK_LSHIFT))	Difence();

	else
	{
		comp.difence = 0;
		comp.consume = -0.8;
	}
}

void NeutralDifence::Difence()
{
	comp.difence = 6;
	comp.consume = .6f;
}

void NeutralDifence::Run()
{
	if (Input::IsKey(DIK_LSHIFT))	Difence();

	else
	{
		comp.difence = 0;
		comp.consume = -0.4;
	}
}