#pragma once
#include "IPlayer.h"


//�e�X�g�V�[�����Ǘ�����N���X
class Server :IPlayer
{
private:

public:
	int InitWinSock();
	int UDPSock();
	int Bind(int sock);
	bool Recv(int sock, DATA* value);
	bool Send(int sock, DATA* value);
};