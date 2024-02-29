#pragma once
#include "Engine/GameObject.h"
#include"Engine/Image.h"
#include"Engine/SceneManager.h"

//�e�X�g�V�[�����Ǘ�����N���X
class TestScene : public GameObject
{
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TestScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

private:

	uint8_t bk;
	uint8_t title;
	
	uint8_t select;

	uint8_t exit;
	uint8_t enter;

};