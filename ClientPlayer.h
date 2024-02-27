#pragma once
#include "IPlayer.h"

//�e�X�g�V�[�����Ǘ�����N���X
class ClientPlayer
{
private:
	uint8_t ID = 0;
	//IPlayer* pIP = new IPlayer;

public:
	int WSASetup();
	int CreateSocket();
	int ConnectToServer(int sock);
	int SetSocketNonBlocking(int sock);
	void SendStruct(int sock);
	void ReceiveStruct(int sock);
	void CleanUp(int sock);
};