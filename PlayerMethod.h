#pragma once
#include"IAttack.h"
#include"IDifence.h"
#include"IJump.h"
#include"IState.h"
#include"Engine/Input.h"

class DashAttack : public IAttack
{
	DashAttack(IPlayer* p);

	void Run() override;
	void Attack() override;
};

class JumpAttack : public IAttack
{
	JumpAttack(IPlayer* p);

	void Run() override;
	void Attack() override;
};

class NeutralAttack : public IAttack
{
	NeutralAttack(IPlayer* p);

	void Run() override;
	void Attack() override;
};

//--------------------

class DashDifence : IDifence
{
	DashDifence(IPlayer* p);

	void Difence() override;
	void Run() override;
};

class JumpDifence : IDifence
{
	JumpDifence(IPlayer* p);

	void Difence() override;
	void Run() override;
};

class NeutralDifence : IDifence
{
	NeutralDifence(IPlayer* p);

	void Difence() override;
	void Run() override;
};

//---------------------

class Jumpable : IJump
{

};

class Unjumpable : IJump
{

};

//----------------------------

class State : IState
{

};