#include "PlayerMethod.h"
#include"IPlayer.h"
#include"Engine/SphereCollider.h"
#include"Engine/GameObject.h"

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

	auto index = parent->comp.msg.cnt;
	float r = 0.3;

	parent->comp.msg.info[index].pos.x = parent->jmp->comp.pos.x + (comp.ray.x * 0.4f);
	parent->comp.msg.info[index].pos.y = parent->jmp->comp.pos.y + (comp.ray.y * 0.4f);
	parent->comp.msg.info[index].pos.z = parent->jmp->comp.pos.z + (comp.ray.z * 0.4f);

	parent->comp.msg.info[index].type = static_cast<uint8_t>(ColliderContext::CC_Attack);
	parent->comp.msg.info[index].size = { r,r,r };
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

	auto index = parent->comp.msg.cnt;
	float r = 0.5;

	parent->comp.msg.info[index].pos.x = parent->jmp->comp.pos.x + (comp.ray.x * 0.2f);
	parent->comp.msg.info[index].pos.y = parent->jmp->comp.pos.y + (comp.ray.y * 0.2f);
	parent->comp.msg.info[index].pos.z = parent->jmp->comp.pos.z + (comp.ray.z * 0.2f);

	parent->comp.msg.info[index].type = static_cast<uint8_t>(ColliderContext::CC_Attack);
	parent->comp.msg.info[index].size = { r,r,r };

	++parent->comp.msg.cnt;
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

	auto index = parent->comp.msg.cnt;
	float r = 0.5;

	parent->comp.msg.info[index].pos.x = parent->jmp->comp.pos.x + (comp.ray.x * 0.2f);
	parent->comp.msg.info[index].pos.y = parent->jmp->comp.pos.y + (comp.ray.y * 0.2f);
	parent->comp.msg.info[index].pos.z = parent->jmp->comp.pos.z + (comp.ray.z * 0.2f);

	parent->comp.msg.info[index].type = static_cast<uint8_t>(ColliderContext::CC_Attack);
	parent->comp.msg.info[index].size = { r,r,r };

	++parent->comp.msg.cnt;
}

//--------------------------------------------

DashDifence::DashDifence(IPlayer* p) :IDifence(p)
{
}

void DashDifence::Difence()
{
	comp.difence = 4;
	comp.consume = .5f;
}

void DashDifence::Run()
{
	if (Input::IsKey(DIK_RSHIFT | DIK_BACKSPACE))	Difence();

	else
	{
		comp.difence = 0;
		comp.consume = -0.1;
	}
}

JumpDifence::JumpDifence(IPlayer* p):IDifence(p)
{
}

void JumpDifence::Difence()
{
	comp.difence = 10;
	comp.consume = 1.0f;
}

void JumpDifence::Run()
{
	if (Input::IsKey(DIK_RSHIFT | DIK_BACKSPACE))	Difence();

	else
	{
		comp.difence = 0;
		comp.consume = -0.8;
	}
}

NeutralDifence::NeutralDifence(IPlayer* p) :IDifence(p)
{
}

void NeutralDifence::Difence()
{
	comp.difence = 6;
	comp.consume = .6f;
}

void NeutralDifence::Run()
{
	if (Input::IsKey(DIK_RSHIFT | DIK_BACKSPACE))	Difence();

	else
	{
		comp.difence = 0;
		comp.consume = -0.4;
	}
}

Jumpable::Jumpable(IPlayer* p) : IJump(p)
{
}

void Jumpable::Jump()
{
	comp.speed = 2;
}

void Jumpable::Run()
{
	if (Input::IsKey(DIK_W))	comp.vec.z += 1;
	if (Input::IsKey(DIK_A))	comp.vec.x +- 1;
	if (Input::IsKey(DIK_S))	comp.vec.z -= 1;
	if (Input::IsKey(DIK_D))	comp.vec.x += 1;

	comp.vec = NormalizeF3(comp.vec);

	if (Input::IsKeyDown(DIK_SPACE))	Jump();
}

Unjumpable::Unjumpable(IPlayer* p) : IJump(p)
{
}

void Unjumpable::Jump()
{

}

void Unjumpable::Run()
{
	Jump();
}

State::State(IPlayer* p):IState(p),da(p),ja(p),na(p),dd(p),nd(p),jd(p),jp(p),ujp(p)
{
	parent->atk = &na;
	parent->dif = &nd;
	parent->jmp = &jp;
	parent->stt = this;
}

void State::Run()
{
	comp.sttbit |= static_cast<uint8_t>(Mask::Running);
	comp.sttbit &= ~(static_cast<uint8_t>(Mask::Running) * !Input::IsKey(DIK_LSHIFT));
//-----------------------------------------

	enum
	{
		jump = 0,
		dash ,
		neutral
	};

	int type = !(comp.sttbit & static_cast<uint8_t>(Mask::Landing)) ? jump 
		: comp.sttbit & static_cast<uint8_t>(Mask::Running) ? dash : neutral;


	switch (type)
	{
	case jump:		parent->atk = &ja;	break;

	case dash:		parent->atk = &da;	break;

	case neutral:	parent->atk = &na;	break;

	default :		parent->atk = &na;	break;
	}

	switch (type)
	{
	case jump:		parent->dif = &jd; break;

	case dash:		parent->dif = &dd; break;

	default:		parent->dif = &nd; break;
	}

	switch (type)
	{
	case jump:		parent->jmp = &ujp; break;

	default:		parent->jmp = &jp;	break;
	}
}