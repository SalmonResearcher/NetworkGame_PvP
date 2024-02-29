#pragma once
#include"IAttack.h"
#include"IDifence.h"
#include"IJump.h"
#include"IState.h"
#include"Engine/Input.h"

class DashAttack : public IAttack
{
public:
	DashAttack(IPlayer* p);

	void Run() override;
	void Attack() override;
};

class JumpAttack : public IAttack
{
public:
	JumpAttack(IPlayer* p);

	void Run() override;
	void Attack() override;
};

class NeutralAttack : public IAttack
{
public:
	NeutralAttack(IPlayer* p);

	void Run() override;
	void Attack() override;
};

//--------------------

class DashDifence : public IDifence
{
public:
	DashDifence(IPlayer* p);

	void Difence() override;
	void Run() override;
};

class JumpDifence : public IDifence
{
public:
	JumpDifence(IPlayer* p);

	void Difence() override;
	void Run() override;
};

class NeutralDifence : public IDifence
{
public:
	NeutralDifence(IPlayer* p);

	void Difence() override;
	void Run() override;
};

//---------------------

class Jumpable : public IJump
{
public:
	Jumpable(IPlayer* p);

	void Jump() override;
	void Run() override;
};

class Unjumpable : public IJump
{
public:
	Unjumpable(IPlayer* p);

	void Jump() override;
	void Run() override;
};

//----------------------------

class State : public IState
{
public:
	State(IPlayer* p);

	void Run() override;

private:

	DashAttack da;
	JumpAttack ja;
	NeutralAttack na;

	DashDifence dd;
	JumpDifence jd;
	NeutralDifence nd;

	Jumpable jp;
	Unjumpable ujp;
};