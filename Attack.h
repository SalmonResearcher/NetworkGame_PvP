#pragma once

class Attack

{
	//俺の脳ではこれしか出なかった←MUNOU
	//変数や関数で足りなと思ったら適当に弄ってクレメンス
public:
	virtual ~Attack() {};
	virtual void attack() = 0;      //攻撃力
	virtual void atk_speed() = 0;   //攻撃速度
	virtual void knock_back() = 0;  //ノックバック量
	virtual void cooldown() = 0;    //クールダウン
	virtual void decision() = 0;    //攻撃判定
};

