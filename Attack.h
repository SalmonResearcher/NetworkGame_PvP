#pragma once

class Attack

{
	//���̔]�ł͂��ꂵ���o�Ȃ�������MUNOU
	//�ϐ���֐��ő���ȂƎv������K���ɘM���ăN�������X
public:
	virtual ~Attack() {};
	virtual void attack() = 0;      //�U����
	virtual void atk_speed() = 0;   //�U�����x
	virtual void knock_back() = 0;  //�m�b�N�o�b�N��
	virtual void cooldown() = 0;    //�N�[���_�E��
	virtual void decision() = 0;    //�U������
};

