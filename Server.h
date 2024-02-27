#pragma once

class IPlayer;

//�e�X�g�V�[�����Ǘ�����N���X
class Server
{
private:
	uint8_t ID = 0;

public:
	int InitWinSock();
	int UDPSock();
	int Bind(int sock);
	bool Recv(int sock, IPlayer::SPlayerComp* recvValue);
	bool Send(int sock, IPlayer::SPlayerComp* playerID);
	int Shutdown(int sock, int listen, int ret);
};